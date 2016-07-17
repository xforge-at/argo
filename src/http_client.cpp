#import "generated/error.hpp"
#import "generated/http_requestor.hpp"
#import "generated/response.hpp"
#import "http_client.hpp"

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

    string bodyString{response.body->begin(), response.body->end()};
    string jsonError;
    auto json_response = Json::parse(bodyString, jsonError);
    if (!jsonError.empty()) {
        this->error(Error{jsonError});
    } else {
        this->success(json_response);
    }
}

void HTTPClient::Callback::receive_error(const Argo::Error &error) {
    this->error(error);
}
