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

MiddlewareResponse HTTPMiddleware::follow_chain(Argo::Response &response) {
    if (next) {
        return next->handle_response(response);
    } else {
        return MiddlewareResponse{ftl::constructor<Argo::Response>(), response};
    }
}

MiddlewareRequest HTTPMiddleware::follow_chain(Argo::Request &request) {
    if (next) {
        return next->handle_request(request);
    } else {
        return MiddlewareRequest{ftl::constructor<Argo::Request>(), request};
    }
}

MiddlewareRequest HTTPMiddleware::break_request_chain(const Error &error) {
    return MiddlewareRequest{ftl::constructor<Argo::Error>(), error};
}

MiddlewareResponse HTTPMiddleware::break_response_chain(const Error &error) {
    return MiddlewareResponse{ftl::constructor<Argo::Error>(), error};
}