#import "util.hpp"
#import <gmock/gmock.h>
#import <gtest/gtest.h>
#import "http_client.hpp"
#import "json_component.hpp"
#import "string_component.hpp"
#import "http_requestor_mock.hpp"
#import "stringify_middleware.hpp"
#import "jsonify_middleware.hpp"
#import "status_code_middleware.hpp"

TEST(HTTPClientTest, MiddlewareChain) {
    nn_shared_ptr<HTTPRequestorMock> requestor = make_not_null(make_shared<HTTPRequestorMock>());

    Json jsonObj = Json::object {
        { "key1", "value1" },
        { "key2", false },
        { "key3", Json::array { 1, 2, 3 } },
        { "key4", 996.8 },
    };
    string tempString = jsonObj.dump();
    std::vector<uint8_t> body{tempString.begin(), tempString.end()};
    Request req{"GET", "www.test.at", nullopt, nullopt};
    Response res{req, 200, unordered_map<string, string>(), make_optional(body)};
    requestor->setResponse(res);

    HTTPClient client{requestor};
    std::unique_ptr<HTTPMiddleware> scm{new StatusCodeMiddleware};
    client.use_middleware(scm);
    std::unique_ptr<HTTPMiddleware> sm{new StringifyMiddleware};
    client.use_middleware(sm);
    std::unique_ptr<HTTPMiddleware> jm{new JsonifyMiddleware};
    client.use_middleware(jm);
    

    client.get("www.test.at",
        [&jsonObj](Response response) {
            optional<Json> newJsonObj = response.get_component<JsonComponent>("bodyJson");
            ASSERT_TRUE(newJsonObj);
            ASSERT_EQ(jsonObj, *newJsonObj);

            optional<string> statusCode = response.get_component<StringComponent>("statusCodeDescription");
            ASSERT_TRUE(statusCode);
            ASSERT_EQ("OK", *statusCode);

        },
        [](Error er) {
        });

}