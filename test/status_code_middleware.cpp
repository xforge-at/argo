#import "status_code_middleware.hpp"
#import "string_component.hpp"
#import "util.h"
#import <gmock/gmock.h>
#import <gtest/gtest.h>

TEST(StatusCodeMiddlewareTest, GetResponseDescription) {
    Request req{"GET", "www.test.at", nullopt, nullopt};
    int32_t code = 202;
    Response res{req, code, unordered_map<string, string>(), nullopt};

    StatusCodeMiddleware scm;
    MiddlewareResponse mr = scm.handle_response(res);

    const Response *response = mr.match([](const Response &r) { return &r; }, [](ftl::otherwise) { return nullptr; });
    ASSERT_TRUE(response);

    let desc = response->get_component<StringComponent>("statusCodeDescription");
    ASSERT_EQ(desc, "Accepted");
}

TEST(StatusCodeMiddlewareTest, GetHttpError) {
    Request req{"GET", "www.test.at", nullopt, nullopt};
    int32_t code = 404;
    Response res{req, code, unordered_map<string, string>(), nullopt};

    StatusCodeMiddleware scm;
    MiddlewareResponse mr = scm.handle_response(res);

    const Error *error = mr.match([](const Error &er) { return &er; }, [](ftl::otherwise) { return nullptr; });
    ASSERT_TRUE(error);
    ASSERT_EQ(error->code, code);
    ASSERT_EQ(error->message, "Not Found");
}