#import "util.hpp"

class HTTPMiddleware;

class MiddlewareChain final {
  public:
    MiddlewareChain();
    ~MiddlewareChain();

    void append(unique_ptr<HTTPMiddleware> &middleware);

    HTTPMiddleware *first();

  private:
    unique_ptr<HTTPMiddleware> head;
    HTTPMiddleware *tail;
};