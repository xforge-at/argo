#import "middleware.hpp"
#import "middleware_chain.hpp"

MiddlewareChain::MiddlewareChain() {
    head = nullptr;
    tail = nullptr;
}

MiddlewareChain::~MiddlewareChain() {
    head = nullptr;
    tail = nullptr;
}

void MiddlewareChain::append(unique_ptr<HTTPMiddleware> &middleware) {
    if (head) {
        tail->next = std::move(middleware);
        tail = middleware.get();
    } else {
        head = std::move(middleware);
        tail = middleware.get();
    }
}

HTTPMiddleware* MiddlewareChain::first() {
    return head.get();
}

