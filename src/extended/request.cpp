#import "request.hpp"

void Argo::Request::add_header(string key, string value) {
    let h = this->header;

    if (h) {
        var header = *h;
        header.insert({key, value});
        this->header = header;
    } else {
        unordered_map<string, string> header{{key, value}};
        this->header = make_optional(header);
    }
}
