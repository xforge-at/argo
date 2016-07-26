#import "generated/error.hpp"
#import "generated/http_requestor.hpp"
#import "http_client.hpp"
#import "middleware.hpp"
#import "request_factory.hpp"
#import <json11/json11.hpp>

HTTPClient::HTTPClient(nn_shared_ptr<HttpRequestor> requestor) : requestor{requestor}, chain() {}
HTTPClient::Callback::Callback(success_block_t success, error_block_t error, HTTPClient *client) : success{success}, error{error}, client(client) {}

HTTPMiddleware *HTTPClient::getFirstMiddleware() {
    return chain.first();
}

void HTTPClient::get(const string &url, success_block_t success, error_block_t error) {
    this->send(HTTPMethod::GET, url, success, error);
}

void HTTPClient::send(HTTPMethod method, const string &url, success_block_t success, error_block_t error) {

    nn_shared_ptr<Callback> cb = make_not_null(make_shared<Callback>(success, error, this));

    var request = RequestFactory::buildRequest(method, url);
    let firstMiddleware = getFirstMiddleware();
    if (firstMiddleware) {
        MiddlewareRequest middlewareRequest = (*firstMiddleware)(request);

        middlewareRequest.matchE([&cb, &requestor = this->requestor ](const Request &request) { requestor->execute_request(request, cb); }, [&cb](const Error &error) { cb->receive_error(error); });
    } else {
        this->requestor->execute_request(request, cb);
    }
}

void HTTPClient::Callback::receive_response(const Argo::Response &response) {

    let firstMiddleware = client->getFirstMiddleware();
    if (firstMiddleware) {
        var tempResponse = Response{response};
        MiddlewareResponse middlewareResponse = (*firstMiddleware)(tempResponse);

        middlewareResponse.matchE([&success_func = this->success](const Response &response) { success_func(response); }, [&error_func = this->error](const Error &error) { error_func(error); });
    } else {
        this->success(response);
    }
}

void HTTPClient::Callback::receive_error(const Argo::Error &error) {
    this->error(error);
}

void HTTPClient::use_middleware(unique_ptr<HTTPMiddleware> &middleware) {
    chain.append(middleware);
}