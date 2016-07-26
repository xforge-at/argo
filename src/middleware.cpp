#import "middleware.hpp"

HTTPMiddleware::HTTPMiddleware() {}

MiddlewareRequest HTTPMiddleware::handle_request(Request &request) {
    return MiddlewareRequest{ftl::constructor<Argo::Request>(), request};
}

MiddlewareResponse HTTPMiddleware::handle_response(Response &response) {
    return MiddlewareResponse{ftl::constructor<Argo::Response>(), response};
}

MiddlewareRequest HTTPMiddleware::operator()(Request &request) {
    return handle_request(request);
}

MiddlewareResponse HTTPMiddleware::operator()(Response &response) {
    return handle_response(response);
}
