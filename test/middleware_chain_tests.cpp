#import "middleware_chain.hpp"
#import "middleware.hpp"
#import "util.hpp"
#import <gmock/gmock.h>
#import <gtest/gtest.h>

class MiddlewareChainTest : public ::testing::Test {
 protected:
  virtual void SetUp() {

  }

  virtual void TearDown() {
    
  }

  MiddlewareChain chain;
};

TEST_F(MiddlewareChainTest, ChainSavesMiddleware) {
  var m = std::make_unique<HTTPMiddleware>();
  var m_copy = m.get();
  chain.append(m);
  ASSERT_EQ(m_copy, chain.first()) << "The Chain's head should be the saved middleware";

  ASSERT_EQ(m_copy, chain.tail()) << "The chain's tail should be the saved middleware";
}

TEST_F(MiddlewareChainTest, ChainEmpty) {
  ASSERT_EQ(nullptr, chain.first()) << "The Chain's head should be nullptr";
  ASSERT_EQ(nullptr, chain.tail()) << "The Chain's tails should be nullptr";
}

TEST_F(MiddlewareChainTest, Order) {
  var m1 = std::make_unique<HTTPMiddleware>();
  var m1_copy = m1.get();
  chain.append(m1);

  var m2 = std::make_unique<HTTPMiddleware>();
  var m2_copy = m2.get();
  chain.append(m2);

  ASSERT_EQ(m1_copy, chain.first());
  ASSERT_EQ(m2_copy, chain.first()->next.get());

  ASSERT_EQ(m1_copy, chain.first()) << "The Chain's head should be the saved middleware";

  ASSERT_EQ(m2_copy, chain.tail()) << "The chain's tail should be the saved middleware";
}