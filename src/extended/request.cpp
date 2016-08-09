#import "request.hpp"
#import <algorithm>
#import <string>

using std::transform;

string normalize_key(const string &key) {
    var normalized_key = string{key};
    transform(key.begin(), key.end(), normalized_key.begin(), ::tolower);
    return normalized_key;
}

void Argo::Request::add_header(const string &key, const string &value) {
    let h = this->header;
    let normalized_key = normalize_key(key);

    if (h) {
        var header = *h;
        // Erase the old header before (if one exists)
        header.erase(normalized_key);
        header.insert({normalized_key, string{value}});
        this->header = header;
    } else {
        unordered_map<string, string> header{{normalized_key, string{value}}};
        this->header = make_optional(header);
    }
}

optional<string> Argo::Request::get_header(const string &key) const {
    let h = this->header;
    if (!h) {
        return nullopt;
    }

    let header = *h;
    let normalized_key = normalize_key(key);
    let result = header.find(normalized_key);
    if (result == header.end()) {
        return nullopt;
    }

    return make_optional(result->second);
}

void Argo::Request::append_to_header(const string &key, const string &value) {
    let result = get_header(key);
    if (!result) {
        add_header(key, value);
        return;
    }
    let previous_value = *result;

    add_header(key, previous_value + "," + value);
}
