#import "string_component.hpp"
#import "stringify_middleware.hpp"
#import "util.h"
#import <gmock/gmock.h>
#import <gtest/gtest.h>

TEST(StringifyMiddlewareTest, ComponentIsSaved) {
    Request req{"GET", "www.test.at", nullopt, nullopt};
    string tempString = "Hello World!";
    std::vector<uint8_t> body{tempString.begin(), tempString.end()};
    Response res{req, 200, unordered_map<string, string>(), make_optional(body)};

    StringifyMiddleware sm;
    MiddlewareResponse mr = sm.handle_response(res);
    const Response *response = mr.match([](const Response &r) { return &r; }, [](ftl::otherwise) { return nullptr; });
    ASSERT_TRUE(response);
    // let stringComp = get_component<StringComponent>("bodyString", *response);
    // let newTempString = stringComp->value();
    let newTempString = response->get_component<StringComponent>("bodyString");
    ASSERT_EQ(tempString, newTempString);
}
