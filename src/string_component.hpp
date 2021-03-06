#import "http_component.hpp"
#import "util.hpp"

struct StringComponent : public HttpComponent {
    using value_type = string;
    StringComponent(string &value) : _value(value) {}
    string value() const { return _value; }

  private:
    const string _value;
};
