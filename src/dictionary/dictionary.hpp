#import "type.hpp"
#import "util.hpp"
#import <exception>
#import <ftl/sum_type.h>
#import <initializer_list>
#import <set>

using std::set;

class dictionary;

using dict_value = ftl::sum_type<int, string, bool, double, dictionary, std::nullptr_t>;
using dict_array = ftl::sum_type<vector<int>, vector<string>, vector<bool>, vector<double>, vector<dictionary>>;

using tree_value = ftl::sum_type<dict_value, dict_array>;

struct tree_node;

struct tree_node_comparator {
	using is_transparent = std::true_type;
	bool operator()(const tree_node &lhs, const tree_node &rhs) const;
	bool operator()(const string &key, const tree_node &rhs) const;
	bool operator()(const tree_node &lhs, const string &key) const;
	bool compare(const string &lhs, const string &rhs) const;
};

class dictionary_adapter {};

class bad_type_exception : public std::runtime_error {
  public:
	bad_type_exception(const string &what) : std::runtime_error(what){};
};

class dictionary {
	/// Allow dictionary adapters to access our private/protected stuff
	friend class dictionary_adapter;

  public:
	/// Constructs an empty dictionary
	dictionary();

	/// Construct a dictionary from a single tree node
	dictionary(tree_node &node);

	/// Construct a dictionary with a list of tree nodes, e.g. { {"key1", "value"}, {"key2", 5}, ... }
	dictionary(std::initializer_list<tree_node> ilist);

	/// Merge the contents of the dictionaries, "this" taking precedence over "other"
	void merge(const dictionary &other);

	/// Merge the contents of the dictionaries, "this" taking precedence, but produce a new dict
	dictionary merge(const dictionary &other) const;

	/// Number of elements in the dictionary
	size_t count() const;

	bool operator==(const dictionary &rhs) const;
    bool operator!=(const dictionary &rhs) const;

	/// Returns the value from the dictionary with the specified type and key pair
	/// Throws on wrong type or non existing key
	template <typename T> const T get(const string &key) const;
	/// Put a value into the dictionary (with the specified type)
	/// Must be one of the types compatible with tree_value
	template <typename T> void put(const string &key, T &value);

	/// Returns true if the specified key exists in the dictionary
	bool exists(const string &key) const;

  private:
	// Uses a custom comparator to only test for the presence of the keys
	set<tree_node, tree_node_comparator> _storage;

	void insert(tree_node &node);
};

struct tree_node {
	string key;
	tree_value value;

	/// Specialization for string values, so tree nodes can be constructed with {"key", "value"}
	tree_node(string _key, const char *_value);

	/// Allow simple construction via {"key", value} for all supported value types
	template <typename T>
	tree_node(string _key, T _value)
	    : key(_key), value(ftl::constructor<dict_value>(), dict_value{ftl::constructor<T>(), _value}) {}

	/// Allow simple construction of arrays via {"key", {a, b, c}} for all supported value types
	/// Note that technically a, b, c could have distinct types, but for this to work all have to be the same type
	/// Having an array with different element types also makes 0% sense
	template <typename T>
	tree_node(string _key, std::initializer_list<T> values)
	    : key(_key), value(ftl::constructor<dict_array>(), dict_array{ftl::constructor<vector<T>>(), values}) {}
    
    template <typename T>
    tree_node(string _key, vector<T> values)
    : key(_key), value(ftl::constructor<dict_array>(), dict_array{ftl::constructor<vector<T>>(), values}) {}
    
    bool operator==(const tree_node &other) const {
        return (this->key == other.key) && (this->value == other.value);
    }
};

template <typename T> const T dictionary::get(const string &key) const {
	let saved = _storage.find(key);
	if (saved == _storage.end()) throw std::out_of_range("no matching key found");
	let result = saved->value.match(
	    [&key](const dict_value &val) {
		    return val.match([](const T &v) { return v; },
		                     [&key](ftl::otherwise) {
			                     throw bad_type_exception{"accessing a key \"" + key + "\" with the wrong type \"" +
			                                              type(T{})};
			                     return T{};
			                 });
		},
        [](const dict_array &val) {
            return val.match([](const T &v) { return v; },
                             [](ftl::otherwise) {
                                 throw bad_type_exception{"accessing vector with the wrong type \"" +
                                     type(T{})};
                                 return T{};
                             });
        },
	    [](ftl::otherwise) { return T{}; });
	return result;
}

template <typename T> void dictionary::put(const string &key, T &value) {
	let node = tree_node{key, value};
	decltype(_storage)::iterator pos;
	bool success;
	int i = 2;
	do {
		std::tie(pos, success) = _storage.insert(node);
		if (!success) {
			_storage.erase(pos);
		}
		i -= 1;
	} while (!success || i > 0);
}
