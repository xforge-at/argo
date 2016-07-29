#import "util.hpp"
#import "http_requestor.hpp"
#import "generated/request.hpp"
#import "generated/error.hpp"
#import "response.hpp"
#import "http_requestor_callback.hpp"

class HTTPRequestorMock : public Argo::HttpRequestor {
    public:
        void setResponse(Argo::Response &response);
        void setError(Argo::Error &error);

        void execute_request(const Argo::Request & request, const nn_shared_ptr<Argo::HttpRequestorCallback> & callback) override;

        Argo::Response *response;
        Argo::Error *error;
};