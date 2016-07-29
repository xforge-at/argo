#import "string_component.hpp"
#import "stringify_middleware.hpp"

MiddlewareResponse StringifyMiddleware::handle_response(Response &response) {
    if (response.body) {
        string bodyString{response.body->begin(), response.body->end()};
        let comp = make_shared<StringComponent>(bodyString);
        response.components.insert({"bodyString", comp});
    }
    return this->follow_chain(response);
}
