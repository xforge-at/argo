#import "util.hpp"
#import <ftl/sum_type.h>

class IsArrayToken {};

using dict_value = ftl::sum_type<int, string, bool, double, IsArrayToken>;
using dict_array = vector<dict_value>;

class dictionary {
  public:
    dictionary();
    virtual ~dictionary();

  private:
    unordered_map<string, dict_value> _storage;
    unordered_map<string, dict_array> _arrayStorage;
};
