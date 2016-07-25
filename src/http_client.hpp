#import "generated/http_requestor.hpp"
#import "generated/http_requestor_callback.hpp"
#import "request_factory.hpp"
#import "http_method.hpp"
#import "util.hpp"
#import <json11/json11.hpp>

using std::function;
using json11::Json;
using Argo::HttpRequestor;
using Argo::Request;
using Argo::Response;
using Argo::Error;

typedef function<void(Json)> success_block_t;
typedef function<void(Error)> error_block_t;

class HTTPClient {
  public:
    virtual ~HTTPClient() {}
    HTTPClient(nn_shared_ptr<HttpRequestor> requestor);

    void get(const string &url, success_block_t success, error_block_t error);

  private:
    nn_shared_ptr<HttpRequestor> requestor;

    void send(HTTPMethod method, const string &url, success_block_t success, error_block_t error);

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
