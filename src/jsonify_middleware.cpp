#import "generated/error.hpp"
#import "json_component.hpp"
#import "jsonify_middleware.hpp"
#import "string_component.hpp"

MiddlewareResponse JsonifyMiddleware::handle_response(Response &response) {
    let tempString = response.get_component<StringComponent>("bodyString");

    string jsonError;
    auto jsonBody = Json::parse(tempString, jsonError);
    if (!jsonError.empty()) {
        let error = Error{0, jsonError};
        return MiddlewareResponse{ftl::constructor<Argo::Error>(), error};
    } else {
        let comp = make_shared<JsonComponent>(jsonBody);
        response.components.insert({"bodyJson", comp});
        return MiddlewareResponse{ftl::constructor<Argo::Response>(), response};
    }
}
