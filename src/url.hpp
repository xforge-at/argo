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

std::string url_encode(const std::string &value);

char from_hex(char ch);

std::string url_decode(const std::string &text);