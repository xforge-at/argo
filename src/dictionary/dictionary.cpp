#import "dictionary.hpp"

#pragma mark - Dictionary

dictionary::dictionary(std::initializer_list<tree_node> _ilist) : _storage(_ilist) {}

dictionary::dictionary(tree_node &node) : _storage({node}) {}

dictionary::dictionary() {}

void dictionary::merge(const dictionary &other) {
    this->_storage.insert(other._storage.begin(), other._storage.end());
}

dictionary dictionary::merge(const dictionary &other) const {
    dictionary new_dict{};
    new_dict._storage.insert(this->_storage.begin(), this->_storage.end());
    new_dict._storage.insert(other._storage.begin(), other._storage.end());
    return new_dict;
}

size_t dictionary::count() const {
	return _storage.size();
}

bool dictionary::exists(const string &key) const {
	let dummy = tree_node{key, "*"};
	return _storage.count(dummy) > 0;
}

#pragma mark - Helper stuff

bool dictionary::operator==(const dictionary &other) const {
    return this->_storage == other._storage;
}

bool dictionary::operator!=(const dictionary &other) const {
    return !(*this == other);
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
