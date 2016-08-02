#import "component_container.hpp"
#import "extended/request.hpp"
#import "generated/request_base.hpp"
#import "http_component.hpp"
#import "util.hpp"
#import <cstdint>
#import <experimental/optional>
#import <string>
#import <unordered_map>
#import <utility>
#import <vector>

namespace Argo {
    struct Request : public RequestBase, public ComponentContainer {
        using ComponentContainer::get_component;

        Request(string method_, string url_, optional<unordered_map<string, string>> header_, optional<vector<uint8_t>> body_) : RequestBase(method_, url_, header_, body_) {}

        virtual ~Request() = default;

        Request(const Request &) = default;
        Request(Request &&) = default;
        Request &operator=(const Request &) = default;
        Request &operator=(Request &&) = default;
    };
}
