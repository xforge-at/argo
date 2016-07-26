#import "middleware.hpp"

MiddlewareRequest HTTPMiddleware::operator()(Request &request) {
    return handle_request(request);
}

MiddlewareResponse HTTPMiddleware::operator()(Response &response) {
    return handle_response(response);
}
