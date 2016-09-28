#import "middleware.hpp"
#import "util.hpp"
#import "dictionary/dictionary.hpp"
#import <json11/json11.hpp>

class DictionaryMiddleware : public HTTPMiddleware {
public:
    MiddlewareResponse handle_response(Response &response) override;
    MiddlewareRequest handle_request(Request &request) override;
    
private:
    tree_value parse_node(const json11::Json &json);
    dictionary parse_dictionary(json11::Json &json);
};
