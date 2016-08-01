#import "http_requestor_mock.hpp"

void HTTPRequestorMock::setResponse(Argo::Response &response) {
    this->response = &response;
}

void HTTPRequestorMock::setError(Argo::Error &error) {
    this->error = &error;
}

void HTTPRequestorMock::execute_request(const Argo::Request & request, const nn_shared_ptr<Argo::HttpRequestorCallback> & callback) {
    if (response) {
        callback->receive_response(*response);
    } else if (error) {
        callback->receive_error(*error);
    }
}