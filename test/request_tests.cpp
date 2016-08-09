#import "extended/request.hpp"
#import "util.hpp"
#import <gmock/gmock.h>
#import <gtest/gtest.h>

using Argo::Request;

TEST(RequestTests, AddHeaderCreatesNewHeaderDict) {
    Request req{"GET", "www.test.at", nullopt, nullopt};

    req.add_header("test_key", "test_value");

    ASSERT_TRUE(req.header) << "New headers should have been created";
    let headerinos = *req.header;
    ASSERT_EQ(headerinos.at("test_key"), "test_value");
}

TEST(RequestTests, AddHeaderLeavesOldDictAlone) {
    let stuff = std::tuple<string, string>{"old_key", "old_value"};
    let m = unordered_map<string, string>{stuff};
    Request req{"GET", "www.test.at", make_optional(m), nullopt};

    req.add_header("test_key", "test_value");

    ASSERT_TRUE(req.header) << "Headers should already exist";
    let headerinos = *req.header;
    ASSERT_EQ(headerinos.at("test_key"), "test_value") << "New values should have been inserted after adding the header";
    ASSERT_EQ(headerinos.at("old_key"), "old_value") << "The old values that were passed during init should still exist";
}

TEST(RequestTests, AddHeaderIsCaseInsensitive) {
    Request req{"GET", "www.test.at", nullopt, nullopt};

    req.add_header("test_key", "test_value2");
    req.add_header("tesT_Key", "test_value1");

    ASSERT_TRUE(req.header) << "Headers should already exist";
    let headerinos = *req.header;
    ASSERT_EQ(headerinos.at("test_key"), "test_value1") << "The first key should have been overwritten";
}

TEST(RequestTests, AddHeaderCanAddMoreThanOneThing) {
    Request req{"GET", "www.test.at", nullopt, nullopt};

    req.add_header("test_key1", "test_value1");
    req.add_header("test_key2", "test_value2");
    req.add_header("test_key3", "test_value3");

    ASSERT_TRUE(req.header) << "Headers should already exist";
    let headerinos = *req.header;
    ASSERT_EQ(headerinos.at("test_key1"), "test_value1") << "New values should have been inserted after adding the header";
    ASSERT_EQ(headerinos.at("test_key2"), "test_value2") << "New values should have been inserted after adding the header";
    ASSERT_EQ(headerinos.at("test_key3"), "test_value3") << "New values should have been inserted after adding the header";
}

TEST(RequestTests, AppendHeaderAddsHeaderIfNoneExists) {
    Request req{"GET", "www.test.at", nullopt, nullopt};

    req.append_to_header("Accept", "test1");

    ASSERT_TRUE(req.header) << "New headers should have been created";
    let headerinos = *req.header;
    ASSERT_EQ(headerinos.at("test_key"), "test_value");
}
