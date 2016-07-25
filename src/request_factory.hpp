#import "generated/request.hpp"
#import "http_method.hpp"
#import "util.hpp"
#import <json11/json11.hpp>

using Argo::Request;
using json11::Json;

class RequestFactory {
  public:
    virtual ~RequestFactory() {}

    static Request buildRequest(HTTPMethod method, const string &url, optional<unordered_map<string, string>> parameters, optional<unordered_map<string, string>> header);
    static Request buildRequest(HTTPMethod method, const string &url, optional<unordered_map<string, string>> parameters);
    static Request buildRequest(HTTPMethod method, const string &url);

    static Request buildRequestWithJSONBody(HTTPMethod method, const string &url, Json &prameters, optional<unordered_map<string, string>> header);
    static Request buildRequestWithJSONBody(HTTPMethod method, const string &url, Json &prameters);

  private:
    RequestFactory() {}
};
