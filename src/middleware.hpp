#import "generated/error.hpp"
#import "generated/request.hpp"
#import "response.hpp"
#import "http_client.hpp"
#import <ftl/sum_type.h>
#import <functional>
#import <memory>

using std::function;
using Argo::Request;
using Argo::Response;

typedef function<Request(Request)> next_request_block;
typedef function<Response(Response)> next_response_block;
typedef ftl::sum_type<Argo::Request, Argo::Error> MiddlewareRequest;
typedef ftl::sum_type<Argo::Response, Argo::Error> MiddlewareResponse;

class HTTPMiddleware {
  public:
    // These must be implemented to handle requests and responses
    virtual MiddlewareRequest handle_request(Request &request);
    virtual MiddlewareResponse handle_response(Response &response);

    // Housekeeping is here
    HTTPMiddleware();

    unique_ptr<HTTPMiddleware> next;

    MiddlewareRequest operator()(Request &request);
    MiddlewareResponse operator()(Response &response);
};
