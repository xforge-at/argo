#import "middleware.hpp"
#import "util.hpp"

class StringifyMiddleware : public HTTPMiddleware {
  public:
    MiddlewareResponse handle_response(Response &response) override;
};