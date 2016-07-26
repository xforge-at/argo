#import "generated/request.hpp"
#import "generated/response_base.hpp"
#import "http_component.hpp"
#import "util.hpp"
#import <cstdint>
#import <experimental/optional>
#import <string>
#import <unordered_map>
#import <utility>
#import <vector>

namespace Argo {
    struct ComponentContainer {
        template <typename T, typename U = typename T::value_type> U get_component(string key) const {
            shared_ptr<T> t = std::static_pointer_cast<T, HttpComponent>(components.at(key));
            return t->value();
        }

        unordered_map<string, shared_ptr<HttpComponent>> components;
    };

    struct Response : public ResponseBase, public ComponentContainer {
        using ComponentContainer::get_component;

        Response(Request request_, int32_t status_code_, std::unordered_map<std::string, std::string> header_, std::experimental::optional<std::vector<uint8_t>> body_)
            : ResponseBase(request_, status_code_, header_, body_) {}

        virtual ~Response() = default;

        Response(const Response &) = default;
        Response(Response &&) = default;
        Response &operator=(const Response &) = default;
        Response &operator=(Response &&) = default;
    };
}
