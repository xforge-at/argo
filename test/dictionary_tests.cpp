#import "dictionary/dictionary.hpp"
#import <gmock/gmock.h>
#import <gtest/gtest.h>

TEST(DictionaryTest, GettingValues) {
	string value = "value";
	tree_node node{"key", value};
	let dict = dictionary{node};

	let result = dict.get<string>(node.key);
	ASSERT_EQ(result, value);
}

TEST(DictionaryTest, GettingArrays) {
	vector<string> value{"hello", "world"};
	tree_node node{"key", value};
	let dict = dictionary{node};

	let result = dict.get<vector<string>>(node.key);
	ASSERT_EQ(result, value);
}

TEST(DictionaryTest, PuttingValues) {
	string key = "test";
	string value = "test_val";
	var d = dictionary{};

	d.put(key, value);

	let result = d.get<string>(key);
	ASSERT_EQ(d.count(), 1) << "There should be exactly one element in the dictionary";
	ASSERT_EQ(result, value);
}

TEST(DictionaryTest, PuttingValuesOverwritesOldValues) {
	string key = "test";
	string value = "test_val";
	string value2 = "test_val2";
	var d = dictionary{};

	d.put(key, value);
	d.put(key, value2);

	let result = d.get<string>(key);
	ASSERT_EQ(d.count(), 1) << "There should be exactly one element in the dictionary";
	ASSERT_EQ(result, value2);
}

TEST(DictionaryTest, PuttingArrays) {
	string key = "test";
	vector<string> value{"hello", "world"};
	var d = dictionary{};

	d.put(key, value);

	let result = d.get<vector<string>>(key);
	ASSERT_EQ(d.count(), 1) << "There should be exactly one element in the dictionary";
	ASSERT_EQ(result, value);
}

TEST(DictionaryTest, Equality) {
	string key = "key", value = "value";
	tree_node node1{key, value};
	tree_node node2{key, value};
	tree_node node3{key, "bla"};

	dictionary dict1{node1}, dict2{node2}, dict3{node3};

	ASSERT_TRUE(dict1 == dict2) << "Two dictionaries with equal contents should be equal!";
	ASSERT_FALSE(dict1 == dict3) << "Two dictionaries with different contents should not be equal";
}

TEST(DictionaryTest, InitializationWithList) {
	let x = dictionary{{"name", "Manu Wallner"},
	                   {"age", 22},
	                   {"awesome", true},
	                   {"stuff", {1, 2, 3, 4, 5}},
	                   {"other_dict", dictionary{{"nested_key", 5}, {"nested_array", {0, 2, 4, 6, 8}}}}};

	ASSERT_EQ(x.count(), 5) << "The dictionary should have been initialized with exactly 5 values";

	ASSERT_EQ(x.get<string>("name"), "Manu Wallner");
	ASSERT_EQ(x.get<int>("age"), 22);
	ASSERT_EQ(x.get<bool>("awesome"), true);

	vector<int> v{1, 2, 3, 4, 5};
	ASSERT_EQ(x.get<vector<int>>("stuff"), v);

	// TODO: Test equality of nested dict here
}

TEST(DictionaryTest, MergingIntoSingleValue) {
	let key = "key";
	let value = "value";
	let key2 = "key2";
	let value2 = "value2";

	var first = dictionary{{key, value}};

	first.merge({{key2, value2}, {key, value2}});

	let key2_value = first.get<string>(key2);
	let key_value = first.get<string>(key);

	ASSERT_EQ(first.count(), 2) << "After merging, there should only be 2 keys";
	// The key that didn't exist in the "first" dict should now be there, and the other one should have kept the value
	ASSERT_EQ(key2_value, value2);
	ASSERT_EQ(key_value, value);
}

TEST(DictionaryTest, MergingIntoOtherDict) {
	let key = "key";
	let value = "value";
	let key2 = "key2";
	let value2 = "value2";

	let first = dictionary{{key, value}};

	let second = first.merge({{key, value2}, {key2, value2}});

	let key2_value = second.get<string>(key2);
	let key_value = second.get<string>(key);

	ASSERT_EQ(second.count(), 2) << "There should be 2 keys in the newly created dict";
	// The key that didn't exist in the "first" dict should now be there, and the other one should have kept the value
	ASSERT_EQ(key2_value, value2);
	ASSERT_EQ(key_value, value);
}
