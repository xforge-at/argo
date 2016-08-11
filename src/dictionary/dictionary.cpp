#import "dictionary.hpp"

#pragma mark - Dictionary

dictionary::dictionary(std::initializer_list<tree_node> _ilist) {
	std::cout << "HI" << std::endl;
}

dictionary::~dictionary() {
	std::cout << "BYE!" << std::endl;
}

#pragma mark - Helper stuff

bool tree_node_comparator::operator()(const tree_node &lhs, const tree_node &rhs) const {
	return lhs.key < rhs.key;
}

tree_node::tree_node(string _key, const char *_value)
    : key(_key), value(ftl::constructor<dict_value>(), dict_value{ftl::constructor<string>(), string{_value}}) {}
