#import "middleware.hpp"
#import "util.hpp"

class JsonifyMiddleware : public HTTPMiddleware {
  public:
    MiddlewareResponse handle_response(Response &response) override;
    MiddlewareRequest handle_request(Request &request) override;
};
