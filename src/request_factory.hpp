#import "generated/request.hpp"
#import "util.hpp"
#import <json11/json11.hpp>

typedef enum HTTPMethod { GET, POST, PUT, PATCH, DELETE } HTTPMethod;

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
