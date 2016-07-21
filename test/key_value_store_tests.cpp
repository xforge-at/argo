#import "key_value_store.hpp"
#import "util.h"
#import <gmock/gmock.h>
#import <gtest/gtest.h>

class KeyValueStoreTest : public ::testing::Test {
 protected:
  virtual void SetUp() {
    path = "test/testStore";
    store = make_shared<KeyValueStore>(path);
  }

  virtual void TearDown() {
    // removing testStore
    // replace with std::experimental::filesystem but import failed
    // std::experimental::filesystem::remove_all(path)
    std::system(("exec rm -r " + path).c_str());
  }

  shared_ptr<KeyValueStore> store;
  string path;
};

TEST_F(KeyValueStoreTest, StringIsSaved) {
  string key = "key1";
  string value = "var1";

  store->putString(key, value);
  optional<string> outString = store->getString(key);
  ASSERT_EQ(value, *outString) << "Strings should be equal";
}

TEST_F(KeyValueStoreTest, StringGetNullopt) {
  optional<string> outString = store->getString("notStoredKey");
  ASSERT_FALSE(outString)<< "String should be nullopt";
}

TEST_F(KeyValueStoreTest, IntIsSaved) {
  string key = "key2";
  int32_t value = 666;

  store->putInt(key, value);
  optional<int32_t> outInt = store->getInt(key);
  ASSERT_EQ(value, *outInt) << "Ints should be equal";
}

TEST_F(KeyValueStoreTest, IntGetNullopt) {
  optional<int32_t> outInt = store->getInt("notStoredKey");
  ASSERT_FALSE(outInt) << "Int should be nullopt";
}