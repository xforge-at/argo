#import "util.hpp"

class HTTPMiddleware;

class MiddlewareChain final {
  public:
    MiddlewareChain();
    ~MiddlewareChain();

    void append(unique_ptr<HTTPMiddleware> &middleware);

    HTTPMiddleware *first();

    HTTPMiddleware *tail() { return _tail; }

  private:
    unique_ptr<HTTPMiddleware> _head;
    HTTPMiddleware *_tail;
};