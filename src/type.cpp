#include "type.hpp"
#include <cstdlib>
#include <cxxabi.h>
#include <memory>

std::string demangle(const char *name) {
	int status = -4; // some arbitrary value to eliminate the compiler warning

	std::unique_ptr<char, void (*)(void *)> res{abi::__cxa_demangle(name, NULL, NULL, &status), std::free};

	return (status == 0) ? res.get() : name;
}
