//  util.hpp
//  libArgo
//
//  Created by Manu Wallner on 30.06.2016.

#pragma once

// URL encode and decode taken from SO: http://stackoverflow.com/questions/154536/encode-decode-urls-in-c
#import <cctype>
#import <iomanip>
#import <sstream>
#import <string>

std::string url_encode(const std::string &value) {
    std::ostringstream escaped;
    escaped.fill('0');
    escaped << std::hex;

    for (auto i = value.cbegin(), n = value.cend(); i != n; ++i) {
        auto c = (*i);

        // Keep alphanumeric and other accepted characters intact
        if (std::isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~') {
            escaped << c;
            continue;
        }

        // Any other characters are percent-encoded
        escaped << std::uppercase;
        escaped << '%' << std::setw(2) << int((unsigned char) c);
        escaped << std::nouppercase;
    }

    return escaped.str();
}

char from_hex(char ch) {
    return std::isdigit(ch) ? ch - '0' : std::tolower(ch) - 'a' + 10;
}

std::string url_decode(const std::string &text) {
    char h;
    std::ostringstream escaped;
    escaped.fill('0');

    for (auto i = text.cbegin(), n = text.cend(); i != n; ++i) {
        std::string::value_type c = (*i);

        if (c == '%') {
            if (i[1] && i[2]) {
                h = from_hex(i[1]) << 4 | from_hex(i[2]);
                escaped << h;
                i += 2;
            }
        } else if (c == '+') {
            escaped << ' ';
        } else {
            escaped << c;
        }
    }

    return escaped.str();
}
