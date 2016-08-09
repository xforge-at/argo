#import "json_component.hpp"
#import "jsonify_middleware.hpp"
#import "stringify_middleware.hpp"
#import "util.hpp"
#import <gmock/gmock.h>
#import <gtest/gtest.h>

TEST(JsonifyMiddlewareTest, ComponentIsSaved) {
    Request req{"GET", "www.test.at", nullopt, nullopt};

    Json jsonObj = Json::object{
        {"key1", "value1"}, {"key2", false}, {"key3", Json::array{1, 2, 3}}, {"key4", 996.8},
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

    optional<Json> newJsonObj = responseJM->get_component<JsonComponent>("bodyJson");
    ASSERT_EQ(jsonObj, *newJsonObj);
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

TEST(JsonifyMiddlewareTest, AcceptEncodingIsAddedForRequest) {
    Request req{"GET", "www.test.at", nullopt, nullopt};

    req.add_header("accept", "application/xml");

    JsonifyMiddleware jm;
    let handled_request = jm.handle_request(req);
    let hr = handled_request.match([](const Request &r) { return &r; }, [](ftl::otherwise) { return nullptr; });
    ASSERT_NE(hr, nullptr);
    ASSERT_NE(hr->header, nullopt);

    let accept_header_value = hr->get_header("Accept");

    ASSERT_TRUE(accept_header_value);
    // TODO: there are better assert macros for string equality
    ASSERT_STRCASEEQ(accept_header_value->c_str(), "application/xml,application/json");
}

TEST(JsonifyMiddlewareTest, NoComponent) {
    Request req{"GET", "www.test.at", nullopt, nullopt};
    Response res{req, 200, unordered_map<string, string>(), nullopt};

    StringifyMiddleware sm;
    MiddlewareResponse mrs = sm.handle_response(res);

    const Response *responseSM = mrs.match([](const Response &r) { return &r; }, [](ftl::otherwise) { return nullptr; });
    ASSERT_TRUE(responseSM);

    JsonifyMiddleware jm;
    Response newRes{*responseSM};
    MiddlewareResponse mrj = jm.handle_response(newRes);
    const Response *responseJM = mrj.match([](const Response &r) { return &r; }, [](ftl::otherwise) { return nullptr; });
    ASSERT_TRUE(responseJM);

    optional<Json> newJsonObj = responseJM->get_component<JsonComponent>("bodyJson");
    ASSERT_FALSE(newJsonObj);
}
