#import "record_getter.hpp"

using std::cout;
using std::endl;

using namespace Argo;

void RecordGetter::get_async_record(const string &prefix) {
    if (this->delegate->should_get_record()) {
        vector<string> stuff{prefix, "hello", "world", "from", "C++", "!"};
        optional<string> test = nullopt;
        optional<int> record_id = 5;
        if (!record_id) {
            cout << "There is no record id" << endl;
        }
        MyRecord record(*record_id, stuff, test);
        dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(3 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
            this->delegate->receive_record(record);
        });
    }
}

void RecordGetter::set_delegate(const nn_shared_ptr<MyRecordGetterDelegate> &delegate) { this->delegate = delegate; }

Argo::RecordGetter::RecordGetter() {}

nn_shared_ptr<MyRecordGetter> MyRecordGetter::create() { return make_not_null(make_shared<RecordGetter>()); }
