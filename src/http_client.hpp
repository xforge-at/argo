#import "generated/http_requestor_callback.hpp"
#import "http_method.hpp"
#import "middleware_chain.hpp"
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
using success_block_t = function<void(Response)>;
using error_block_t = function<void(Error)>;

class HTTPClient {
    friend class HTTPMiddleware;

  public:
    virtual ~HTTPClient() {} // TODO: cancel http requestor
    HTTPClient(nn_shared_ptr<HttpRequestor> requestor);

    void get(const string &url, success_block_t success, error_block_t error);
    void post(const string &url, success_block_t success, error_block_t error);
    void put(const string &url, success_block_t success, error_block_t error);
    void patch(const string &url, success_block_t success, error_block_t error);
    void deleterino_in_pastrami(const string &url, success_block_t success, error_block_t error);

    void use_middleware(unique_ptr<HTTPMiddleware> &middleware);

  private:
    nn_shared_ptr<HttpRequestor> requestor;
    MiddlewareChain chain;

    void send(HTTPMethod method, const string &url, success_block_t success, error_block_t error);

    HTTPMiddleware *getFirstMiddleware();

    class Callback : public Argo::HttpRequestorCallback {
      public:
        Callback(success_block_t success, error_block_t error, HTTPClient *client);
        void receive_response(const Response &response) override;
        void receive_error(const Error &error) override;

      private:
        success_block_t success;
        error_block_t error;
        HTTPClient *client;
    };
};
