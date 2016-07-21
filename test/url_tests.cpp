#import "url.hpp"
#import <gmock/gmock.h>
#import <gtest/gtest.h>

TEST(URLEncodeTest, SpacesAreEncoded) {
    auto baseString = "hello world";
    auto urlEncoded = url_encode(baseString);
    ASSERT_EQ(urlEncoded, "hello%20world") << "Spaces should have been encoded";
}

TEST(URLEncodeTest, RegularStringsStayTheSame) {
    auto baseString = "thisIsAStringThatCanBeUsedInURLsUnchanged";
    auto urlEncoded = url_encode(baseString);
    auto urlDecoded = url_decode(baseString);

    ASSERT_EQ(baseString, urlEncoded) << "A string with no special symbols should stay the same with encode/decode";
    ASSERT_EQ(urlDecoded, urlEncoded) << "A string with no special symbols should stay the same with encode/decode";
    ASSERT_EQ(baseString, urlDecoded) << "A string with no special symbols should stay the same with encode/decode";
}

TEST(URLEncodeTest, EncodeDecodeShouldBeEqual) {
    auto baseString = "https://www.AStringWithMany special$symbols.com/\\Blabla/?q=t&b=p";
    auto urlEncoded = url_encode(baseString);
    auto urlDecoded = url_decode(urlEncoded);

    ASSERT_EQ(baseString, urlDecoded) << "URL encode -> decode should yield the original string";
}
