//
//  dictionary_component.hpp
//  libArgo
//
//  Created by Michael Heinzl on 28.09.16.
//
//

#import "http_component.hpp"
#import "util.hpp"
#import "dictionary/dictionary.hpp"

struct DictionaryComponent : public HttpComponent {
    using value_type = dictionary;
    DictionaryComponent(dictionary &value) : _value(value) {}
    dictionary value() const { return _value; }
    
private:
    const dictionary _value;
};
