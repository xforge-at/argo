#import "component_container.hpp"
#import "extended/request.hpp"
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
    struct Response : public ResponseBase, public ComponentContainer {

        Response(Request request_, int32_t status_code_, std::unordered_map<std::string, std::string> header_, std::experimental::optional<std::vector<uint8_t>> body_)
            : ResponseBase(request_, status_code_, header_, body_) {}

        virtual ~Response() = default;

        Response(const Response &) = default;
        Response(Response &&) = default;
        Response &operator=(const Response &) = default;
        Response &operator=(Response &&) = default;

        // Extended methods:
        using ComponentContainer::get_component;
    };
}
