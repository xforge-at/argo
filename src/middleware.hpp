#import "generated/request.hpp"
#import "generated/response.hpp"
#import "http_client.hpp"
#import <functional>
#import <memory>

using std::function;
using Argo::Request;
using Argo::Response;

using next_request_block = function<Request(Request)>;
using next_response_block = function<Response(Response)>;

class HTTPMiddleware {
  public:
    // These must be implemented to handle requests and responses
    virtual Request handle_request(Request &request, next_request_block &next) = 0;
    virtual Response handle_response(Response &response, next_response_block &next) = 0;

    // Housekeeping is here
    HTTPMiddleware(nn_shared_ptr<HTTPClient> &client);

    Request handle_request(Request &request);
    Response handle_response(Response &response);

    next_request_block &get_next_request_block();
    next_response_block &get_next_response_block();

    template <typename T> T perform_with_client(function<T(nn_shared_ptr<HTTPClient>)> &action);

  private:
    // Use weak pointer because _client holds a reference to this middleware
    std::weak_ptr<HTTPClient> _client;
};
