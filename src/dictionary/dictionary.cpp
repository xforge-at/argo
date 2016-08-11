#import "dictionary.hpp"

#pragma mark - Dictionary

dictionary::dictionary(std::initializer_list<tree_node> _ilist) {
	std::cout << "HI" << std::endl;
}

dictionary::dictionary(tree_node &node) {}

dictionary::dictionary() {}

void dictionary::merge(const dictionary &other) {}
dictionary dictionary::merge(const dictionary &other) const {}
size_t dictionary::count() const {}

template <typename T> T *dictionary::get(const string &key) const {
	return nullptr;
}
template <typename T> void put(const string &key, T &value) {}

// Explicitly instantiate supported types
#define init_with_type(type)                                                                                           \
	template type *dictionary::get(const string &key) const;                                                           \
	template void put(const string &key, type &value);                                                                 \
	template vector<type> *dictionary::get(const string &key) const;                                                   \
	template void put(const string &key, vector<type> &value);
init_with_type(int) init_with_type(string) init_with_type(bool) init_with_type(double) init_with_type(dictionary)
#undef init_with_type

#pragma mark - Helper stuff

    bool dictionary::operator==(const dictionary &other) const {
	return false;
}

bool tree_node_comparator::operator()(const tree_node &lhs, const tree_node &rhs) const {
	return compare(lhs.key, rhs.key);
}
bool tree_node_comparator::operator()(const string &key, const tree_node &rhs) const {
	return compare(key, rhs.key);
}
bool tree_node_comparator::operator()(const tree_node &lhs, const string &key) const {
	return compare(lhs.key, key);
}
bool tree_node_comparator::compare(const string &lhs, const string &rhs) const {
	return lhs < rhs;
}

tree_node::tree_node(string _key, const char *_value)
    : key(_key), value(ftl::constructor<dict_value>(), dict_value{ftl::constructor<string>(), string{_value}}) {}
