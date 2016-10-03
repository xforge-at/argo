#import "jsonify_middleware.hpp"
#import "generated/error.hpp"
#import "json_component.hpp"
#import "string_component.hpp"
#import <cassert>

vector<uint8_t> stringToBinary(const string &str) {
    return vector<uint8_t>{str.begin(), str.end()};
}

MiddlewareResponse JsonifyMiddleware::handle_response(Response &response) {
    let tempString = response.get_component<StringComponent>("bodyString");
    if (!tempString) return follow_chain(response);

    string jsonError;
    auto jsonBody = Json::parse(*tempString, jsonError);
    if (!jsonError.empty()) {
        let error = Error{0, jsonError};
        return break_response_chain(error);
    } else {
        let comp = make_shared<JsonComponent>(jsonBody);
        response.components.insert({"bodyJson", comp});
        return follow_chain(response);
    }
}

MiddlewareRequest JsonifyMiddleware::handle_request(Request &request) {
    let jsonBody = request.get_component<JsonComponent>("bodyJson");
    
    if (jsonBody) {
        let jsonString = jsonBody->dump();
        request.body = make_optional(stringToBinary(jsonString));
        request.add_header("Content-Type", "application/json");
    }
    
    request.append_to_header("accept", "application/json");
    return follow_chain(request);
}
