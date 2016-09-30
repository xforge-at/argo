#import "request_factory.hpp"
#import "url.hpp"
#import <algorithm>
#import <cassert>

string methodToString(HTTPMethod method) {
    switch (method) {
        case GET:
            return "GET";
        case POST:
            return "POST";
        case PATCH:
            return "PATCH";
        case DELETE:
            return "DELETE";
        case PUT:
            return "PUT";
    }
    assert(false);
    return "ERR";
}

using std::ostringstream;

string parametersToString(unordered_map<string, string> parameters) {
    string str = std::accumulate(parameters.begin(), parameters.end(), string{},
                                 [](string &buf, let &param) {
                                     let keyString = url_encode(param.first);
                                     let valueString = url_encode(param.second);
                                     if (!buf.empty()) {
                                         return buf + "&" + keyString + "=" + valueString;
                                     }
                                     return keyString + "=" + valueString;
                                 });

    return str;
}

vector<uint8_t> stringToBinary(string &str) {
    return vector<uint8_t>{str.begin(), str.end()};
}

Request buildRequestWithContentType(HTTPMethod method, const string &url, optional<string> body,  optional<string> contentType, optional<unordered_map<string, string>> header) {
    let methodString = methodToString(method);
    var bodyData = body ? make_optional(stringToBinary(*body)) : nullopt;
    var request = Request{methodString, url, header, bodyData};
    
    if (contentType) {
        request.append_to_header("Content-Type", *contentType);
    }
    
    return request;
}

Request RequestFactory::buildRequest(HTTPMethod method, const string &url, optional<unordered_map<string, string>> parameters, optional<unordered_map<string, string>> header) {
    var urlString = string{url};
    optional<string> bodyString = nullopt;
    optional<string> contentType = nullopt;

    switch (method) {
        case GET:
            if (parameters) {
                urlString = urlString + "?" + parametersToString(*parameters);
            }
            break;
        case POST:
        case PATCH:
        case DELETE:
        case PUT:
            if (parameters) {
                bodyString = parametersToString(*parameters);
                contentType = string{"application/x-www-form-urlencoded"};
            }
            break;
    }

    return buildRequestWithContentType(method, urlString, bodyString, contentType, header);
}

Request RequestFactory::buildRequest(HTTPMethod method, const string &url, optional<unordered_map<string, string>> parameters) {
    return RequestFactory::buildRequest(method, url, parameters, nullopt);
}

Request RequestFactory::buildRequest(HTTPMethod method, const string &url) {
    return RequestFactory::buildRequest(method, url, nullopt);
}
