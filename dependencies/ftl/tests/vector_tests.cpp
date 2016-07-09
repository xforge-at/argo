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
#include <ftl/vector.h>
#include <list>
#include "vector_tests.h"

test_set vector_tests{
	std::string("vector"),
	{
		std::make_tuple(
			std::string("concatMap[&]"),
			std::function<bool()>([]() -> bool {
				std::vector<int> v{1,2,3,4};

				auto v2 = ftl::concatMap(
					[](int x){
						return std::vector<int>{2*x, 2*x-1};
					},
					v
				);

				return v2 == std::vector<int>{2,1,4,3,6,5,8,7};
			})
		),
		std::make_tuple(
			std::string("concatMap[&&]"),
			std::function<bool()>([]() -> bool {

				auto v = ftl::concatMap(
					[](int x){
						return std::vector<int>{2*x, 2*x-1};
					},
					std::vector<int>{2,3,4}
				);

				return v == std::vector<int>{4,3,6,5,8,7};
			})
		),
		std::make_tuple(
			std::string("monoid::id"),
			std::function<bool()>([]() -> bool {

				return ftl::monoid<std::vector<float>>::id().empty();
			})
		),
		std::make_tuple(
			std::string("monoid::append[&,&]"),
			std::function<bool()>([]() -> bool {
				using ftl::operator^;

				auto v1 = std::vector<int>{1,2};
				auto v2 = std::vector<int>{2,3};

				return (v1 ^ v2) == std::vector<int>{1,2,2,3};
			})
		),
		std::make_tuple(
			std::string("monoid::append[&,&&]"),
			std::function<bool()>([]() -> bool {
				using ftl::operator^;

				auto v1 = std::vector<int>{1,2};
				auto v2 = std::vector<int>{2,3};

				return (v1 ^ std::move(v2)) == std::vector<int>{1,2,2,3};
			})
		),
		std::make_tuple(
			std::string("monoid::append[&&,&]"),
			std::function<bool()>([]() -> bool {
				using ftl::operator^;

				auto v1 = std::vector<int>{1,2};
				auto v2 = std::vector<int>{2,3};

				return (std::move(v1) ^ v2) == std::vector<int>{1,2,2,3};
			})
		),
		std::make_tuple(
			std::string("monoid::append[&&,&&]"),
			std::function<bool()>([]() -> bool {
				using ftl::operator^;

				auto v1 = std::vector<int>{1,2};
				auto v2 = std::vector<int>{2,3};

				return
					(std::move(v1) ^ std::move(v2)) == std::vector<int>{1,2,2,3};
			})
		),
		std::make_tuple(
			std::string("functor::map[a->b,&"),
			std::function<bool()>([]() -> bool {
				using ftl::operator%;

				auto f = [](int x){ return float(x)+1.f; };
				auto v = std::vector<int>{1,2,3};
				auto v2 = f % v;

				return v2 == std::vector<float>{2.f,3.f,4.f};
			})
		),
		std::make_tuple(
			std::string("functor::map[a->b,&&"),
			std::function<bool()>([]() -> bool {
				using ftl::operator%;

				auto f = [](int x){ return float(x)+1.f; };
				auto v = f % std::vector<int>{1,2,3};

				return v == std::vector<float>{2.f,3.f,4.f};
			})
		),
		std::make_tuple(
			std::string("functor::map[a->a,&&"),
			std::function<bool()>([]() -> bool {
				using ftl::operator%;

				auto f = [](int x){ return x+1; };
				auto v = f % std::vector<int>{1,2,3};

				return v == std::vector<int>{2,3,4};
			})
		),
		std::make_tuple(
			std::string("applicative::pure"),
			std::function<bool()>([]() -> bool {

				auto v = ftl::applicative<std::vector<int>>::pure(2);

				return v == std::vector<int>{2};
			})
		),
		std::make_tuple(
			std::string("applicative::apply"),
			std::function<bool()>([]() -> bool {
				using ftl::operator*;

				std::vector<ftl::function<int(int)>> vf{
					[](int x){ return x-1; },
					[](int x){ return x+1; }
				};

				std::vector<int> v = vf * std::vector<int>{1,2,3};

				return v == std::vector<int>{0,1,2,2,3,4};
			})
		),
		std::make_tuple(
			std::string("monad::bind[&,->vector]"),
			std::function<bool()>([]() -> bool {
				using ftl::operator>>=;

				std::vector<int> v{1,2,3};

				auto f = [](int x){ return std::vector<int>{x,x+1}; };

				return (v >>= f) == std::vector<int>{1,2,2,3,3,4};
			})
		),
		std::make_tuple(
			std::string("monad::bind[&,->list]"),
			std::function<bool()>([]() -> bool {
				using ftl::operator>>=;

				std::vector<int> v{1,2,3,4};

				auto f = [](int x){
					return x % 2 == 0 ? std::list<int>{x} : std::list<int>{};
				};

				return (v >>= f) == std::vector<int>{2,4};
			})
		),
		std::make_tuple(
			std::string("monad::bind[&&,->maybe]"),
			std::function<bool()>([]() -> bool {
				using ftl::operator>>=;

				auto f = [](int x){
					return x % 2 == 0 ? std::list<int>{x} : std::list<int>{};
				};

				return
					(std::vector<int>{1,2,3,4} >>= f)
					== std::vector<int>{2,4};
			})
		),
		std::make_tuple(
			std::string("foldable::foldl"),
			std::function<bool()>([]() -> bool {
				using namespace ftl;

				std::vector<int> v{1,2,3};
				auto f = [](int x, int y){ return x+y; };


				return foldl(f, 0, v) == 6;
			})
		),
		std::make_tuple(
			std::string("foldable::foldr"),
			std::function<bool()>([]() -> bool {
				using namespace ftl;

				std::vector<float> v{4.f,4.f,2.f};
				auto f = [](float x, float y){ return x/y; };


				return foldr(f, 16.f, v) == .125f;
			})
		),
		std::make_tuple(
			std::string("foldable::fold"),
			std::function<bool()>([]() -> bool {
				using namespace ftl;

				std::vector<prod_monoid<int>> v{prod(2),prod(3),prod(2)};


				return fold(v) == 12;
			})
		),
		std::make_tuple(
			std::string("zippable::zipWith[3,3]"),
			std::function<bool()>([]() -> bool {
				using namespace ftl;

				std::vector<int> v1{1,2,3};
				std::vector<int> v2{2,2,2};

				auto v3 = zipWith([](int x, int y){ return x + y; }, v1, v2);

				return v3 == std::vector<int>{3,4,5};
			})
		),
		std::make_tuple(
			std::string("zippable::zipWith[2,3]"),
			std::function<bool()>([]() -> bool {
				using namespace ftl;

				std::vector<int> v1{1,2};
				std::vector<int> v2{2,2,2};

				auto v3 = zipWith([](int x, int y){ return x + y; }, v1, v2);

				return v3 == std::vector<int>{3,4};
			})
		),
		std::make_tuple(
			std::string("zippable::zipWith[3,2]"),
			std::function<bool()>([]() -> bool {
				using namespace ftl;

				std::vector<int> v1{1,2,3};
				std::vector<int> v2{2,2};

				auto v3 = zipWith([](int x, int y){ return x + y; }, v1, v2);

				return v3 == std::vector<int>{3,4};
			})
		),
		std::make_tuple(
			std::string("zippable::zipWith[0,3]"),
			std::function<bool()>([]() -> bool {
				using namespace ftl;

				std::vector<int> v1{};
				std::vector<int> v2{2,2};

				auto v3 = zipWith([](int x, int y){ return x + y; }, v1, v2);

				return v3 == std::vector<int>{};
			})
		),
		std::make_tuple(
			std::string("zippable::zipWith[3,0]"),
			std::function<bool()>([]() -> bool {
				using namespace ftl;

				std::vector<int> v1{1,2,3};
				std::vector<int> v2{};

				auto v3 = zipWith([](int x, int y){ return x + y; }, v1, v2);

				return v3 == std::vector<int>{};
			})
		),
		std::make_tuple(
			std::string("zippable::zip[3,3]"),
			std::function<bool()>([]() -> bool {
				using namespace ftl;

				std::vector<int> v1{1,2,3};
				std::vector<float> v2{3.f,2.f,1.f};

				auto v3 = zip(v1, v2);

				return v3 == std::vector<std::tuple<int,float>>{
					std::make_tuple(1,3.f),
					std::make_tuple(2,2.f),
					std::make_tuple(3,1.f)
				};
			})
		)
	}
};

