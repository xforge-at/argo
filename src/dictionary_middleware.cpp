#import "dictionary_middleware.hpp"
#import "generated/error.hpp"
#import "dictionary_component.hpp"
#import "string_component.hpp"

using json11::Json;

MiddlewareResponse DictionaryMiddleware::handle_response(Response &response) {
    let tempString = response.get_component<StringComponent>("bodyString");
    if (!tempString) return follow_chain(response);
    
    string jsonError;
    auto jsonBody = Json::parse(*tempString, jsonError);
    if (!jsonError.empty()) {
        let error = Error{0, jsonError};
        return break_response_chain(error);
    } else {
        dictionary dict = this->parse_dictionary(jsonBody);
        let comp = make_shared<DictionaryComponent>(dict);
        response.components.insert({"bodyDictionary", comp});
        return follow_chain(response);
    }
}

tree_value DictionaryMiddleware::parse_node(const json11::Json &json) {
    switch (json.type()) {
        case Json::OBJECT:
        {
            dictionary dict{};
            for (let &kv : json.object_items()) {
                tree_value value = this->parse_node(kv.second);

            }
            break;
        }
        
        case Json::ARRAY:
        {
            for (let &v : json.array_items()) {
                
            }
            
            
            break;
        }
        case Json::BOOL:
            return tree_value{ftl::constructor<dict_value>(), dict_value{ftl::constructor<bool>(), json.bool_value()}};
        case Json::STRING:
            return tree_value{ftl::constructor<dict_value>(), dict_value{ftl::constructor<string>(), json.string_value()}};
        case Json::NUMBER:
            return tree_value{ftl::constructor<dict_value>(), dict_value{ftl::constructor<double>(), json.number_value()}};
        case Json::NUL:
            return tree_value{ftl::constructor<dict_value>(), dict_value{ftl::constructor<std::nullptr_t>(), nullptr}};
    }

    return tree_value{ftl::constructor<dict_value>(), dict_value{ftl::constructor<int>(), 5}};
}

MiddlewareRequest DictionaryMiddleware::handle_request(Request &request) {
    request.append_to_header("accept", "application/json");
    return follow_chain(request);
}
