#import "generated/http_requestor_callback.hpp"
#import "http_method.hpp"
#import "util.hpp"

namespace Argo {
    class HttpRequestor;
    struct Response;
    struct Request;
    struct Error;
}
namespace json11 {
    class Json;
}
class HTTPMiddleware;

using std::function;
using json11::Json;
using Argo::HttpRequestor;
using Argo::Response;
using Argo::Request;
using Argo::Error;
using success_block_t = function<void(Json)>;
using error_block_t = function<void(Error)>;

class HTTPClient {
    friend class HTTPMiddleware;

  public:
    virtual ~HTTPClient() {}
    HTTPClient(nn_shared_ptr<HttpRequestor> requestor);

    void get(const string &url, success_block_t success, error_block_t error);

    template <typename T> void use_middleware();
    void use_middleware(HTTPMiddleware &middleware);

  private:
    nn_shared_ptr<HttpRequestor> requestor;
    vector<HTTPMiddleware> _middlewares;

    void send(HTTPMethod method, const string &url, success_block_t success, error_block_t error);

    function<Request(Request)> get_next_request_block(HTTPMiddleware &current);
    function<Response(Response)> get_next_response_block(HTTPMiddleware &current);

    class Callback : public Argo::HttpRequestorCallback {
      public:
        Callback(success_block_t success, error_block_t error);
        void receive_response(const Response &response) override;
        void receive_error(const Error &error) override;

      private:
        success_block_t success;
        error_block_t error;
    };
};
