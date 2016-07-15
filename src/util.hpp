//  util.hpp
//  libArgo
//
//  Created by Manu Wallner on 30.06.2016.

#pragma once

// Swift-like variable declaration
#define let const auto
#define var auto

// Most important STL headers
#import <iostream>
#import <map>
#import <memory>
#import <string>
#import <unordered_map>
#import <utility>
#import <vector>

using std::shared_ptr;
using std::string;
using std::vector;
using std::make_shared;
using std::map;
using std::unordered_map;

// What would we even do without GCD?
#import <dispatch/dispatch.h>

// Optional support
#import <experimental/optional>

using std::experimental::optional;
using std::experimental::make_optional;
using std::experimental::nullopt;
using std::experimental::nullopt_t;

// Use the gsl to make our code more expressive
#import <gsl.h>

using gsl::not_null;
using gsl::owner;
using gsl::span;
using gsl::string_span;
using gsl::finally;

// Helpers for Djinni to be able to use the not_null from the GSL
template <typename T> using nn_shared_ptr = not_null<shared_ptr<T>>;

// Glorious C++14 return type deduction
template <typename T> inline decltype(auto) make_not_null(T x) { return not_null<T>(x); }

// URL encode and decode taken from SO: http://stackoverflow.com/questions/154536/encode-decode-urls-in-c
#import <cctype>
#import <iomanip>
#import <sstream>

string url_encode(const string &value) {
    std::ostringstream escaped;
    escaped.fill('0');
    escaped << std::hex;

    for (string::const_iterator i = value.begin(), n = value.end(); i != n; ++i) {
        string::value_type c = (*i);

        // Keep alphanumeric and other accepted characters intact
        if (std::isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~') {
            escaped << c;
            continue;
        }

        // Any other characters are percent-encoded
        escaped << std::uppercase;
        escaped << '%' << std::setw(2) << int((unsigned char)c);
        escaped << std::nouppercase;
    }

    return escaped.str();
}

char from_hex(char ch) { return std::isdigit(ch) ? ch - '0' : std::tolower(ch) - 'a' + 10; }

string url_decode(string text) {
    char h;
    std::ostringstream escaped;
    escaped.fill('0');

    for (auto i = text.begin(), n = text.end(); i != n; ++i) {
        string::value_type c = (*i);

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
