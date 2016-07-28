#import "http_component.hpp"
#import "util.h"
#import <json11/json11.hpp>

struct JsonComponent : public HttpComponent {
    using value_type = json11::Json;
    JsonComponent(json11::Json &value) : _value(value) {}
    json11::Json value() const { return _value; }

  private:
    const json11::Json _value;
};
