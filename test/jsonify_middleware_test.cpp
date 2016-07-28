#import "json_component.hpp"
#import "stringify_middleware.hpp"
#import "jsonify_middleware.hpp"
#import "util.h"
#import <gmock/gmock.h>
#import <gtest/gtest.h>

TEST(JsonifyMiddlewareTest, ComponentIsSaved) {
    Request req{"GET", "www.test.at", nullopt, nullopt};

    Json jsonObj = Json::object {
        { "key1", "value1" },
        { "key2", false },
        { "key3", Json::array { 1, 2, 3 } },
        { "key4", 996.8 },
    };
    string tempString = jsonObj.dump();
    std::vector<uint8_t> body{tempString.begin(), tempString.end()};
    Response res{req, 200, unordered_map<string, string>(), make_optional(body)};

    StringifyMiddleware sm;
    MiddlewareResponse mrs = sm.handle_response(res);

    const Response *responseSM = mrs.match([](const Response &r) { return &r; }, [](ftl::otherwise) { return nullptr; });
    ASSERT_TRUE(responseSM);

    JsonifyMiddleware jm;
    Response newRes{*responseSM};
    MiddlewareResponse mrj = jm.handle_response(newRes);
    const Response *responseJM = mrj.match([](const Response &r) { return &r; }, [](ftl::otherwise) { return nullptr; });
    ASSERT_TRUE(responseJM);
    
    let newJsonObj = responseJM->get_component<JsonComponent>("bodyJson");
    ASSERT_EQ(jsonObj, newJsonObj);
}

TEST(JsonifyMiddlewareTest, InvalidJson) {
    Request req{"GET", "www.test.at", nullopt, nullopt};

    string tempString = "I'm an invalid json string |}{|";
    std::vector<uint8_t> body{tempString.begin(), tempString.end()};
    Response res{req, 200, unordered_map<string, string>(), make_optional(body)};

    StringifyMiddleware sm;
    MiddlewareResponse mrs = sm.handle_response(res);

    const Response *responseSM = mrs.match([](const Response &r) { return &r; }, [](ftl::otherwise) { return nullptr; });
    ASSERT_TRUE(responseSM);

    JsonifyMiddleware jm;
    Response newRes{*responseSM};
    MiddlewareResponse mrj = jm.handle_response(newRes);
    const Error *error = mrj.match([](const Error &er) { return &er; }, [](ftl::otherwise) { return nullptr; });
    ASSERT_TRUE(error);
}
