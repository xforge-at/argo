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
        Request(string method_, string url_, optional<unordered_map<string, string>> header_, optional<vector<uint8_t>> body_) : RequestBase(method_, url_, header_, body_) {}

        virtual ~Request() = default;

        Request(const Request &) = default;
        Request(Request &&) = default;
        Request &operator=(const Request &) = default;
        Request &operator=(Request &&) = default;

        // Extended methods:

        using ComponentContainer::get_component;
        /// Replace the header with 'key' if it exists
        void add_header(const string &key, const string &value);
        /// If the header with 'key' exists, append the value to the value list
        void append_to_header(const string &key, const string &value);
        /// Normalizes key before lookup
        optional<string> get_header(const string &key) const;
    };
}
