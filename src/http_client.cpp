#import "generated/error.hpp"
#import "generated/http_requestor.hpp"
#import "http_client.hpp"
#import "middleware.hpp"
#import "request_factory.hpp"
#import <json11/json11.hpp>
#import "json_component.hpp"

HTTPClient::HTTPClient(nn_shared_ptr<HttpRequestor> requestor) : requestor{requestor}, chain() {}
HTTPClient::Callback::Callback(success_block_t success, error_block_t error, HTTPClient *client) : success{success}, error{error}, client(client) {}


// GET

void HTTPClient::get(const string &url, success_block_t success, error_block_t error) {
    this->send(HTTPMethod::GET, url, nullopt, nullopt, success, error);
}

void HTTPClient::get(const string &url, unordered_map<string, string> parameters, success_block_t success, error_block_t error) {
    this->send(HTTPMethod::GET, url, parameters, nullopt, success, error);
}

// POST

void HTTPClient::post(const string &url, success_block_t success, error_block_t error) {
    this->send(HTTPMethod::POST, url, nullopt, nullopt, success, error);
}

void HTTPClient::post(const string &url, json11::Json &json, success_block_t success, error_block_t error) {
    this->send(HTTPMethod::POST, url, nullopt, json, success, error);
}

void HTTPClient::post(const string &url, unordered_map<string, string> parameters, success_block_t success, error_block_t error) {
    this->send(HTTPMethod::POST, url, parameters, nullopt, success, error);
}

// PUT

void HTTPClient::put(const string &url, success_block_t success, error_block_t error) {
    this->send(HTTPMethod::PUT, url, nullopt, nullopt, success, error);
}

void HTTPClient::put(const string &url, json11::Json &json, success_block_t success, error_block_t error) {
    this->send(HTTPMethod::PUT, url, nullopt, json, success, error);
}

void HTTPClient::put(const string &url, unordered_map<string, string> parameters, success_block_t success, error_block_t error) {
    this->send(HTTPMethod::PUT, url, parameters, nullopt, success, error);
}

// PATCH

void HTTPClient::patch(const string &url, success_block_t success, error_block_t error) {
    this->send(HTTPMethod::PATCH, url, nullopt, nullopt, success, error);
}

void HTTPClient::patch(const string &url, json11::Json &json, success_block_t success, error_block_t error) {
    this->send(HTTPMethod::PATCH, url, nullopt, json, success, error);
}

void HTTPClient::patch(const string &url, unordered_map<string, string> parameters, success_block_t success, error_block_t error) {
    this->send(HTTPMethod::PATCH, url, parameters, nullopt, success, error);
}

// DELETE

void HTTPClient::deleterino_in_pastrami(const string &url, success_block_t success, error_block_t error) {
    this->send(HTTPMethod::DELETE, url, nullopt, nullopt, success, error);
}


// Private Methos

void HTTPClient::send(HTTPMethod method, const string &url, optional<unordered_map<string, string>> parameters, optional<json11::Json> body, success_block_t success, error_block_t error) {

    nn_shared_ptr<Callback> cb = make_not_null(make_shared<Callback>(success, error, this));

    var request = RequestFactory::buildRequest(method, url, parameters);
    
    if (body) {
        let comp = make_shared<JsonComponent>(*body);
        request.components.insert({"bodyJson", comp});
    }
    
    let firstMiddleware = getFirstMiddleware();
    if (firstMiddleware) {
        MiddlewareRequest middlewareRequest = (*firstMiddleware)(request);

        middlewareRequest.matchE([&cb, &requestor = this->requestor ](const Request &request) { requestor->execute_request(request, cb); }, [&cb](const Error &error) { cb->receive_error(error); });
    } else {
        this->requestor->execute_request(request, cb);
    }
}

// Callback

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

// Middleware

HTTPMiddleware *HTTPClient::getFirstMiddleware() {
    return chain.first();
}

void HTTPClient::use_middleware(unique_ptr<HTTPMiddleware> &middleware) {
    chain.append(middleware);
}
