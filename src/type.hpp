#import <string>
#import <typeinfo>

std::string demangle(const char *name);

template <class T> std::string type(const T &t) {
	return demangle(typeid(t).name());
}
