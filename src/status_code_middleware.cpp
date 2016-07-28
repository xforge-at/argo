#import "generated/error.hpp"
#import "status_code_middleware.hpp"
#import "string_component.cpp"

StatusCodeMiddleware::StatusCodeMiddleware() {
    statusCodes = {{100, "Continue"},
                   {101, "Switching Protocols"},
                   {200, "OK"},
                   {201, "Created"},
                   {202, "Accepted"},
                   {203, "Non-Authoritative Information"},
                   {204, "No Content"},
                   {205, "Reset Content"},
                   {206, "Partial Content"},
                   {300, "Multiple Choices"},
                   {301, "Moved Permanently"},
                   {302, "Found"},
                   {303, "See Other"},
                   {304, "Not Modified"},
                   {305, "Use Proxy"},
                   {307, "Temporary Redirect"},
                   {400, "Bad Request"},
                   {401, "Unauthorized"},
                   {402, "Payment Required"},
                   {403, "Forbidden"},
                   {404, "Not Found"},
                   {405, "Method Not Allowed"},
                   {406, "Not Acceptable"},
                   {407, "Proxy Authentication Required"},
                   {408, "Request Timeout"},
                   {409, "Conflict"},
                   {410, "Gone"},
                   {411, "Length Required"},
                   {412, "Precondition Failed"},
                   {413, "Request Entity Too Large"},
                   {414, "Request-URI Too Long"},
                   {415, "Unsupported Media Type"},
                   {416, "Requested Range Not Satisfiable"},
                   {417, "Expectation Failed"},
                   {500, "Internal Server Error"},
                   {501, "Not Implemented"},
                   {502, "Bad Gateway"},
                   {503, "Service Unavailable"},
                   {504, "Gateway Timeout"},
                   {505, "HTTP Version Not Supported"}};
}

MiddlewareResponse StatusCodeMiddleware::handle_response(Response &response) {
    let status_code = response.status_code;
    string description = statusDescription(status_code);
    if (status_code >= 400) {
        let error = Error{status_code, description};
        return MiddlewareResponse{ftl::constructor<Argo::Error>(), error};
    } else {
        let comp = make_shared<StringComponent>(description);
        response.components.insert({"statusCodeDescription", comp});
        return MiddlewareResponse{ftl::constructor<Argo::Response>(), response};
    }
}

string StatusCodeMiddleware::statusDescription(int32_t code) {
    auto t = statusCodes.find(code);
    if (t == statusCodes.end()) return "Unknown Status Code";
    return t->second;
}