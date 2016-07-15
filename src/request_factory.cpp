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
    string str = std::accumulate(parameters.begin(), parameters.end(), string{}, [](string &buf, let &param) {
        let keyString = url_encode(param.first);
        let valueString = url_encode(param.second);
        if (!buf.empty()) {
            return buf + "&" + keyString + "=" + valueString;
        }
        return keyString + "=" + valueString;
    });

    return str;
}

vector<uint8_t> stringToBinary(string &str) { return vector<uint8_t>{str.begin(), str.end()}; }

Request buildRequestWithContentType(HTTPMethod method, string url, optional<string> body, string contentType, optional<unordered_map<string, string>> header) {
    let methodString = methodToString(method);

    let contentTypeHeader = std::make_pair("Content-Type", contentType);
    unordered_map<string, string> headerMap;

    if (header) {
        header->insert(contentTypeHeader);
        headerMap = *header;
    } else {
        headerMap = {contentTypeHeader};
    }

    var bodyData = body ? make_optional(stringToBinary(*body)) : nullopt;
    return Request{methodString, url, make_optional(headerMap), bodyData};
}

Request RequestFactory::buildRequest(HTTPMethod method, string url, optional<unordered_map<string, string>> parameters, optional<unordered_map<string, string>> header) {
    let paramString = parameters ? parametersToString(*parameters) : "";
    var urlString = string{url};
    var bodyString = string{};

    switch (method) {
        case GET:
            if (parameters) {
                urlString = urlString + "?" + paramString;
            }
            break;
        case POST:
        case PATCH:
        case DELETE:
        case PUT:
            bodyString = paramString;
            break;
    }

    return buildRequestWithContentType(method, urlString, bodyString.empty() ? nullopt : make_optional(bodyString), "application/x-www-form-urlencoded", header);
}

Request RequestFactory::buildRequest(HTTPMethod method, string url, optional<unordered_map<string, string>> parameters) {
    // nop
    return RequestFactory::buildRequest(method, url, nullopt, nullopt);
}

Request RequestFactory::buildRequest(HTTPMethod method, string url) { return RequestFactory::buildRequest(method, url, nullopt); }

Request RequestFactory::buildRequestWithJSONBody(HTTPMethod method, string url, Json parameters, optional<unordered_map<string, string>> header) {
    switch (method) {
        case POST:
        case PATCH:
        case PUT:
            break;
        case GET:
        case DELETE:
            assert(false);
            break;
    }

    return buildRequestWithContentType(method, url, make_optional(parameters.dump()), "application/json", header);
}

Request RequestFactory::buildRequestWithJSONBody(HTTPMethod method, string url, Json parameters) { return RequestFactory::buildRequestWithJSONBody(method, url, parameters, nullopt); }
