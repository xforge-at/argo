#import "http_component.hpp"

struct ComponentContainer {
    template <typename T, typename U = typename T::value_type> optional<U> get_component(string key) const {
        try {
            shared_ptr<T> t = std::static_pointer_cast<T, HttpComponent>(components.at(key));
            return t->value();
        } catch (std::out_of_range ex) {
            return nullopt;
        }
    }

    unordered_map<string, shared_ptr<HttpComponent>> components;
};
