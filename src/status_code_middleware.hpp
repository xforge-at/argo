#import "middleware.hpp"
#import "util.hpp"

class StatusCodeMiddleware : public HTTPMiddleware {
  public:
    StatusCodeMiddleware();
    MiddlewareResponse handle_response(Response &response) override;

  private:
    unordered_map<int32_t, string> statusCodes;
    string statusDescription(int32_t code);
};