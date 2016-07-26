#import "http_component.hpp"
#import "util.h"

struct StringComponent : public HttpComponent {
    StringComponent(string &value) : _value(value) {}
    string value() const { return _value; }

  private:
    const string _value;
};