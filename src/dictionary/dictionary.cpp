#import "dictionary.hpp"

#pragma mark - Dictionary

dictionary::dictionary(std::initializer_list<tree_node> _ilist) : _storage(_ilist) {}

dictionary::dictionary(tree_node &node) : _storage({node}) {}

dictionary::dictionary() {}

void dictionary::merge(const dictionary &other) {}
dictionary dictionary::merge(const dictionary &other) const {
	return dictionary{};
}
size_t dictionary::count() const {
	return _storage.size();
}

#pragma mark - Helper stuff

bool dictionary::operator==(const dictionary &other) const {
	return this->count() == other.count();
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
