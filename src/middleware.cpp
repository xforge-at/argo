#import "middleware.hpp"
#import "generated/request.hpp"
#import "generated/response.hpp"

Request HTTPMiddleware::handle_request(Request &request) {
    this->handle_request(request, this->get_next_request_block());
}
Response HTTPMiddleware::handle_response(Response &response) {
    this->handle_response(response, this->get_next_response_block());
}

HTTPMiddleware::HTTPMiddleware(nn_shared_ptr<HTTPClient> &client) : _client(client.get()) {}

next_request_block &HTTPMiddleware::get_next_request_block() {
    auto self = this;
    return this->perform_with_client([&self](nn_shared_ptr<HTTPClient> &client) { client->get_next_request_block(self); });
}
next_response_block &HTTPMiddleware::get_next_response_block() {
    auto self = this;
    return this->perform_with_client([&self](nn_shared_ptr<HTTPClient> &client) { client->get_next_response_block(self); });
}

template <typename T> T HTTPMiddleware::perform_with_client(function<T(nn_shared_ptr<HTTPClient>)> &action) {
    auto _c = _client.lock();
    assert(_c != nullptr);
    auto client = make_not_null(_c);
    return action(client);
}
