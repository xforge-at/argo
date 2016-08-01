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
using std::unique_ptr;
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
template <typename T> inline decltype(auto) make_not_null(T x) {
    return not_null<T>(x);
}
