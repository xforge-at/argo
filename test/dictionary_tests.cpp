#import "dictionary/dictionary.hpp"
#import <gmock/gmock.h>
#import <gtest/gtest.h>

TEST(DictionaryTest, GettingValues) {
	string value = "value";
	tree_node node{"key", value};
	let dict = dictionary{node};

	let result = dict.get<string>(node.key);
	ASSERT_EQ(*result, value);
}

TEST(DictionaryTest, PuttingValues) {
	string key = "test";
	string value = "test_val";
	var d = dictionary{};

	d.put(key, value);

	let result = d.get<string>(key);
	ASSERT_EQ(*result, value);
}

TEST(DictionaryTest, Equality) {
	string key = "key", value = "value";
	tree_node node1{key, value};
	tree_node node2{key, value};

	let dict1{node1}, dict2{node2};

	ASSERT_TRUE(dict1 == dict2) << "Two dictionaries with equal contents should be equal!";
}

TEST(DictionaryTest, InitializationWithList) {
	let x = dictionary{{"name", "Manu Wallner"},
	                   {"age", 22},
	                   {"awesome", true},
	                   {"stuff", {1, 2, 3, 4, 5}},
	                   {"other_dict", dictionary{{"nested_key", 5}, {"nested_array", {0, 2, 4, 6, 8}}}}};
	ASSERT_EQ(*x.get<string>("name"), "Manu Wallner");
	ASSERT_EQ(*x.get<int>("age"), 22);
	ASSERT_EQ(*x.get<bool>("awesome"), true);

	vector<int> v{1, 2, 3, 4, 5};
	ASSERT_EQ(*x.get<vector<int>>("stuff"), v);
}

TEST(DictionaryTest, MergingIntoSingleValue) {
	let key = "key";
	let value = "value";
	let key2 = "key2";
	let value2 = "value2";

	var first = dictionary{{key, value}};

	first.merge({{key2, value2}, {key, value2}});

	let key2_value = *first.get<string>(key2);
	let key_value = *first.get<string>(key);

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

	let key2_value = *second.get<string>(key2);
	let key_value = *second.get<string>(key);

	// The key that didn't exist in the "first" dict should now be there, and the other one should have kept the value
	ASSERT_EQ(key2_value, value2);
	ASSERT_EQ(key_value, value);
}
