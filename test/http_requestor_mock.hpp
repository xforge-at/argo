#import "extended/request.hpp"
#import "extended/response.hpp"
#import "generated/error.hpp"
#import "http_requestor.hpp"
#import "http_requestor_callback.hpp"
#import "util.hpp"

class HTTPRequestorMock : public Argo::HttpRequestor {
  public:
    void setResponse(Argo::Response &response);
    void setError(Argo::Error &error);

    void execute_request(const Argo::Request &request, const nn_shared_ptr<Argo::HttpRequestorCallback> &callback) override;

    Argo::Response *response;
    Argo::Error *error;
};
