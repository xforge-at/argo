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

TEST(RequestTests, GetHeaderReturnsNullOpt) {
    Request req{"GET", "www.test.at", nullopt, nullopt};

    let result = req.get_header("test_key");

    ASSERT_FALSE(result) << "When no key exists, get_header should return nullopt";
}

TEST(RequestTests, GetHeaderReturnsTheValue) {
    Request req{"GET", "www.test.at", nullopt, nullopt};

    let header_key = string{"test_key1"};
    let header_value = string{"test_value"};
    req.add_header(header_key, header_value);
    let result = req.get_header(header_key);

    ASSERT_TRUE(result) << "When the key exists, get_header should return the value";
    ASSERT_EQ(header_value, *result);
}

TEST(RequestTests, GetHeaderIsCaseInsensitive) {
    Request req{"GET", "www.test.at", nullopt, nullopt};

    let header_key = string{"test_key1"};
    let header_key_upcase = string{"TEST_KEY1"};
    let header_value = string{"test_value"};
    req.add_header(header_key, header_value);
    let result1 = req.get_header(header_key);
    let result2 = req.get_header(header_key_upcase);

    ASSERT_TRUE(result1) << "When the key exists, get_header should return the value";
    ASSERT_TRUE(result2) << "When the key exists, get_header should return the value";
    ASSERT_EQ(*result1, *result2);
}

TEST(RequestTests, AppendHeaderAddsHeaderIfNoneExists) {
    Request req{"GET", "www.test.at", nullopt, nullopt};

    let header_key = string{"accept"};
    let header_value = string{"application/json"};
    req.append_to_header(header_key, header_value);

    ASSERT_TRUE(req.header) << "New headers should have been created";
    let headerinos = *req.header;
    ASSERT_EQ(headerinos.at(header_key), header_value);
}

TEST(RequestTests, AppendHeaderAppendsToExistingHeader) {
    let header_key = string{"accept"};
    let header_value = string{"application/json"};

    let stuff = std::tuple<string, string>{header_key, header_value};
    let m = unordered_map<string, string>{stuff};
    Request req{"GET", "www.test.at", make_optional(m), nullopt};

    req.append_to_header(header_key, "application/xml");

    ASSERT_TRUE(req.header) << "New headers should have been created";
    let headerinos = *req.header;

    ASSERT_EQ(headerinos.at(header_key), "application/json,application/xml");
}
