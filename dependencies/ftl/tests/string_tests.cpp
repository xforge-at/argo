/*
 * Copyright (c) 2013 Björn Aili
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 * claim that you wrote the original software. If you use this software
 * in a product, an acknowledgment in the product documentation would be
 * appreciated but is not required.
 *
 * 2. Altered source versions must be plainly marked as such, and must not be
 * misrepresented as being the original software.
 *
 * 3. This notice may not be removed or altered from any source
 * distribution.
 */
#include <ftl/string.h>
#include "string_tests.h"

test_set string_tests{
	std::string("string"),
	{
		std::make_tuple(
			std::string("monoid::id"),
			std::function<bool()>([]() -> bool {
				return ftl::monoid<std::string>::id() == std::string("");
			})
		),
		std::make_tuple(
			std::string("monoid::append[&,&]"),
			std::function<bool()>([]() -> bool {
				using ftl::operator^;

				auto s1 = std::string("ab");
				auto s2 = std::string("cd");

				return (s1 ^ s2) == std::string("abcd");
			})
		),
		std::make_tuple(
			std::string("monoid::append[&,&&]"),
			std::function<bool()>([]() -> bool {
				using ftl::operator^;

				auto s1 = std::string("ab");
				auto s2 = std::string("cd");

				return (s1 ^ std::move(s2)) == std::string("abcd");
			})
		),
		std::make_tuple(
			std::string("monoid::append[&&,&]"),
			std::function<bool()>([]() -> bool {
				using ftl::operator^;

				auto s1 = std::string("ab");
				auto s2 = std::string("cd");

				return (std::move(s1) ^ s2) == std::string("abcd");
			})
		),
		std::make_tuple(
			std::string("monoid::append[&&,&&]"),
			std::function<bool()>([]() -> bool {
				using ftl::operator^;

				auto s1 = std::string("ab");
				auto s2 = std::string("cd");

				return (std::move(s1) ^ std::move(s2)) == std::string("abcd");
			})
		)
	}
};

