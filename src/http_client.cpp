#import "http_client.hpp"
#import "generated/error.hpp"
#import "generated/http_requestor.hpp"
#import "middleware.hpp"
#import "request_factory.hpp"
#import <json11/json11.hpp>

using next_request_block = function<Request(Request)>;
using next_response_block = function<Response(Response)>;

HTTPClient::HTTPClient(nn_shared_ptr<HttpRequestor> requestor) : requestor{requestor} {}
HTTPClient::Callback::Callback(success_block_t success, error_block_t error) : success{success}, error{error} {}

void HTTPClient::get(const string &url, success_block_t success, error_block_t error) {
    this->send(HTTPMethod::GET, url, success, error);
}

void HTTPClient::send(HTTPMethod method, const string &url, success_block_t success, error_block_t error) {

    nn_shared_ptr<Callback> cb = make_not_null(make_shared<Callback>(success, error));

    // add session token

    let request = RequestFactory::buildRequest(method, url);
    this->requestor->execute_request(request, cb);
}

void HTTPClient::Callback::receive_response(const Argo::Response &response) {

    // check http status code
    let status_code = response.status_code;
    if (status_code >= 400) {
        this->error(Error{status_code, ""});
    } else {
        // parse JSON
        string bodyString{response.body->begin(), response.body->end()};
        string jsonError;
        auto json_response = Json::parse(bodyString, jsonError);
        if (!jsonError.empty()) {
            this->error(Error{0, jsonError});
        } else {
            this->success(json_response);
        }
    }
}

void HTTPClient::Callback::receive_error(const Argo::Error &error) {
    this->error(error);
}

template <typename T> void HTTPClient::use_middleware() {
    _middlewares.push_back(T(make_not_null(this)));
}

void HTTPClient::use_middleware(HTTPMiddleware &middleware) {
    _middlewares.push_back(middleware);
}
