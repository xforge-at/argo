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

//String

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

// Int

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

TEST_F(KeyValueStoreTest, IntGetNulloptFormatException) {
  string key = "key3";
  string value = "var";

  store->putString(key, value);
  optional<int32_t> outInt = store->getInt(key);
  ASSERT_FALSE(outInt) << "Int should be nullopt because of format exception";
}

// Double

TEST_F(KeyValueStoreTest, DoubleIsSaved) {
  string key = "key4";
  double value = 666.666;

  store->putDouble(key, value);
  optional<double> outDouble = store->getDouble(key);
  ASSERT_EQ(value, *outDouble) << "Doubles should be equal";
}

TEST_F(KeyValueStoreTest, DoubleGetNullopt) {
  optional<double> outDouble = store->getDouble("notStoredKey");
  ASSERT_FALSE(outDouble) << "Double should be nullopt";
}

TEST_F(KeyValueStoreTest, DoubleGetNulloptFormatException) {
  string key = "key5";
  string value = "var";

  store->putString(key, value);
  optional<double> outDouble = store->getDouble(key);
  ASSERT_FALSE(outDouble) << "Double should be nullopt because of format exception";
}

// Float

TEST_F(KeyValueStoreTest, FloatIsSaved) {
  string key = "key6";
  float value = 99.99;

  store->putFloat(key, value);
  optional<float> outFloat = store->getFloat(key);
  ASSERT_EQ(value, *outFloat) << "Floats should be equal";
}

TEST_F(KeyValueStoreTest, FloatGetNullopt) {
  optional<float> outFloat = store->getFloat("notStoredKey");
  ASSERT_FALSE(outFloat) << "Float should be nullopt";
}

TEST_F(KeyValueStoreTest, FloatGetNulloptFormatException) {
  string key = "key7";
  string value = "var";

  store->putString(key, value);
  optional<float> outFloat = store->getFloat(key);
  ASSERT_FALSE(outFloat) << "Float should be nullopt because of format exception";
}
