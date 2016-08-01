#import "middleware.hpp"
#import "middleware_chain.hpp"

MiddlewareChain::MiddlewareChain() {
    _head = nullptr;
    _tail = nullptr;
}

MiddlewareChain::~MiddlewareChain() {
    _head = nullptr;
    _tail = nullptr;
}

void MiddlewareChain::append(unique_ptr<HTTPMiddleware> &middleware) {
    var raw = middleware.get();
    if (_head) {
        _tail->next = std::move(middleware);
        _tail = raw;
    } else {
        _head = std::move(middleware);
        _tail = raw;
    }
}

HTTPMiddleware *MiddlewareChain::first() {
    return _head.get();
}
