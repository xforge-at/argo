#import "generated/my_record.hpp"
#import "generated/my_record_getter.hpp"
#import "generated/my_record_getter_delegate.hpp"

#import "util.hpp"

namespace Argo {

class RecordGetter : public MyRecordGetter {
  public:
    virtual ~RecordGetter() { delegate = nullptr; }
    RecordGetter();
    void get_async_record(const string &prefix) override;
    void set_delegate(const nn_shared_ptr<MyRecordGetterDelegate> &delegate) override;

  private:
    shared_ptr<MyRecordGetterDelegate> delegate;
};
}
