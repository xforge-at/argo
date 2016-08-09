#import "request.hpp"
#import <algorithm>
#import <string>

using std::transform;

void Argo::Request::add_header(string key, string value) {
    let h = this->header;

    var normalized_key = string{key};
    transform(key.begin(), key.end(), normalized_key.begin(), ::tolower);

    if (h) {
        var header = *h;
        // Erase the old header before (if one exists)
        header.erase(normalized_key);
        header.insert({normalized_key, value});
        this->header = header;
    } else {
        unordered_map<string, string> header{{normalized_key, value}};
        this->header = make_optional(header);
    }
}
