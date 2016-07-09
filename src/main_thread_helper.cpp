#import "generated/main_thread_dispatch_queue_helper.hpp"
#ifdef __ANDROID__

#import <dispatch/dispatch.h>
#import <sys/select.h>

using namespace Argo;

class main_thread_helper : public MainThreadDispatchQueueHelper {
  public:
    main_thread_helper();
    virtual ~main_thread_helper() override{};
    void drain_queue() override;
    bool wait_for_items(int32_t timeout_microseconds) override;

  private:
    dispatch_queue_handle_t _handle;
};

main_thread_helper::main_thread_helper() : _handle(dispatch_get_main_queue_handle_np()) {}

bool main_thread_helper::wait_for_items(int32_t timeout_microseconds) {
    fd_set readable_set;
    FD_ZERO(&readable_set);
    FD_SET(this->_handle, &readable_set);

    struct timeval time;
    time.tv_sec = 0;
    time.tv_usec = timeout_microseconds;

    return select(this->_handle + 1, &readable_set, NULL, NULL, timeout_microseconds != 0 ? &time : NULL) > 0;
}

void main_thread_helper::drain_queue() { dispatch_main_queue_drain_np(); }

nn_shared_ptr<MainThreadDispatchQueueHelper> Argo::MainThreadDispatchQueueHelper::create() { return make_not_null(make_shared<main_thread_helper>()); }

#endif
