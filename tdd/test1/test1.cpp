#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <deque>

#include "deque.h"

template <typename C, typename F, typename P, typename X>
::testing::AssertionResult Expect_Throw(C & c, F f, P p, X x, const std::string & s = "") {
  try {
    (c.*f)(p); 
  }
  catch (X & x) {
      if (0 == s.size() || std::string(x.what()).find(s) == 0 ) {
          return ::testing::AssertionSuccess(); 
      } else {
          return ::testing::AssertionFailure() << "Wrong what() \nExpected: " << s << "\nActual: " << x.what(); 
      }
  }
  catch (std::exception & e) {
      return ::testing::AssertionFailure() << "Other std::exception\ntypeinfo: " << typeid(e).name() << "\nwhat(): " << typeid(e).name(); 
  }
  catch (...) {
      return ::testing::AssertionFailure() << "Other unknown exception"; 
  }
  return ::testing::AssertionFailure() << "Exception expected, but not thrown"; 
}

class MockVector : public impl_t<int, 16> {
public: 
    using base_t = impl_t<int, 16>; 

    MockVector() {
      ON_CALL( *this, size() ).WillByDefault(::testing::Invoke(&base, &base_t::size));
      ON_CALL( *this, empty() ).WillByDefault(::testing::Invoke(&base, &base_t::empty));
      // ON_CALL( *this, push_back(::testing::_) ).WillByDefault(::testing::Invoke(&base, static_cast<void(base_t::*) (const base_t::value_type&)> &base_t::empty));
    }

    MOCK_CONST_METHOD0( size, size_t());
    MOCK_CONST_METHOD0( empty, bool()); 
    // MOCK_METHOD1(push_back, void(const base_t::value_type & )); 
private: 
    base_t & base = *this;
};

template <MockVector DEQ<int, 16, MockVector>::* T >
struct private_access {
    friend MockVector DEQ<int, 16, MockVector>::* getPtrs() {return T; }
}; 

MockVector DEQ<int, 16, MockVector>::* getPtrs(); 

template struct private_access< &DEQ<int, 16, MockVector>>::mPtrs>

TEST ( Create, Trivial) {
  DEQ<int>        di;
  DEQ<double, 10> d10; 
  DEQ<double, 10, std::deque<std::unique_ptr< std::array<double, 10> > > > dd;  // csak azt ellenőrzi, hogy a template helyes-e; 

  const DEQ<int> cdi(std::move(di)); 
  const DEQ<double, 10> cd10(std::move(d10)); 
  const DEQ<double, 10, std::deque<std::unique_ptr< std::array<double, 10> > > > cdd(std::move(dd));

}

TEST (Create, Size) {
    DEQ<int, 16, MockVector> di;
    MockVector DEQ<int, 16, MockVector>::*ptrToPtrs = getPtrs(); 

    MockVector &ptrs = di.*ptrToPtrs;

    EXPECT_CALL(ptrs, size()).Times(0);
    EXPECT_CALL(ptrs, empty()).Times(1);
    // EXPECT_CALL(ptrs, push_back(::testing::_)).Times(0);

    EXPECT_EQ(0, di.size());
    EXPECT_TRUE(di.empty());
    
    EXPECT_TRUE(ptrs.empty()); 
}

TEST (PushBack, OnceAfterEmpty) {
  DEQ<int> di; 
  MockVector & ptrs = di.getImpl(); 
  
  // EXPECT_CALL(ptrs, push_back(::testing::_)).Times(0);
  di.push_back(1);

  ASSERT_FALSE(di.empty()); 
  ASSERT_EQ(1, di.size()); 
  EXPECT_EQ(1, di.front()); 
  EXPECT_EQ(1, di.back()); 
}

TEST (PushBack, ManyAfterCreate) {
  const int n = 42; 
  DEQ<int> di; 

  for (int i = 0; i < n; i++) {
      di.push_back( i * i); 
      ASSERT_EQ(i*i, di.back()); 
      ASSERT_EQ(0, di.front()); 
      ASSERT_EQ(i+1, di.size()); 
  }
}

TEST (PopBack, PopBackAfterPushBack) {
   const int n = 42; 
   DEQ<int> di; 
   for (int i = 0; i < n; i++) {
       di.push_back(i*i); 
   }
   ASSERT_NO_THROW( di.at(n-1)); 
   di.pop_back(); 
   ASSERT_THROW( di.at(n-1), std::out_of_range); 

   EXPECT_EQ(n-1, di.size()); 
   EXPECT_EQ(0, di.front()); 
   EXPECT_EQ((n-2)*(n-2), di.back()); 

   for(int i = 0; i < n-1; i++) {
     ASSERT_EQ(i*i, di.at(i)); 
   }
   
}

TEST (PopBack, ManyPopBackAfterPushBack) {
    const int n = 942; 

    DEQ<int> di; 
    for (int i = 0; i < n; i++) {
      di.push_back(i*i); 
    }
    for (int i = 0; i < n; i++) {
        ASSERT_EQ(n-i, di.size());
        ASSERT_EQ((n-i-1)*(n-i-1), di.back() ); 
        di.pop_back(); 
    }
    EXPECT_EQ(0, di.size()); 
    EXPECT_THROW( di.at(0), std::out_of_range); 
}

TEST (PushBack, ManyAfterPopBackCreate) {
  const int nPush1  = 142; 
  const int nPop    = 77; 
  const int nPush2  = 93; 

  static_assert(nPush1 >= nPop, "error: nPush1 < nPop");

  DEQ<int> di; 

  for (int i = 0; i < nPush1; i++) {
      di.push_back( i * i);  
  }
  for (int i = 0; i < nPop; i++) {
      di.pop_back();  
  }
  for (int i = 0; i < nPush2; i++) {
      int k = nPush1 - nPop + i; 
      di.push_back( k * k * k );  
  }

  EXPECT_EQ(nPush1 - nPop + nPush2, di.size()); 

  for (int i = 0; i < di.size(); i++) {
    SCOPED_TRACE( std::to_string(i));
    if ( i < nPush1 - nPop) {
      ASSERT_EQ(i * i, di.at(i)); 
    } else {
      ASSERT_EQ( i * i * i, di.at(i));
    }
  }
}


TEST (Index, AfterPush) {
  const int n = 42; 
  DEQ<int> di; 

  for (int i = 0; i < n; i++) {
      di.push_back( i * i); 
  }
  ASSERT_EQ(n, di.size()); 

  for (int i = 0; i < n; i++) {
      ASSERT_EQ(i*i, di[i]);
  }
}


TEST (Index, AfterUpdate) {
  const int n = 142; 
  const int k = 55; 
  const int j = 66;
  DEQ<int> di; 

  static_assert( k + j <= n, "[k, k+j-1] shoulld be inside [0, n-1]"); 
  for (int i = 0; i < n; i++) {
      di.push_back( i * i); 
  }
  ASSERT_EQ(n, di.size()); 
  for (int i = k; i < k + j; i++) {
      di[i] = di[i] + 1000;
  }
  for (int i = 0; i < n; i++) {
      if (i >= k && i < k + j) {
        ASSERT_EQ(i*i + 1000, di[i]);
      } else {
        ASSERT_EQ(i*i, di[i]);
      }
  }
}

TEST (At, AfterPush) {

  using at_t = int & (DEQ<int>::*)(size_t); 
  using at_t_c = const int & (DEQ<int>::*)(size_t) const; 

  at_t AtFunc       = &DEQ<int>::at; 
  at_t_c AtFuncConst  = &DEQ<int>::at; 

  const int n = 42; 
  DEQ<int> di; 

  for (int i = 0; i < n; i++) {
      di.push_back( i * i); 
  }
  ASSERT_EQ(n, di.size()); 

  const DEQ<int> & cdi = di; 

  for (int i = 0; i < n; i++) {
      EXPECT_NO_THROW(cdi.at(i)); 
      ASSERT_EQ(i*i, cdi.at(i));
  }

  EXPECT_TRUE(Expect_Throw(cdi, AtFuncConst, di.size()      , std::out_of_range(""), "Bad index" ));
  EXPECT_TRUE(Expect_Throw(cdi, AtFuncConst, di.size()+1    , std::out_of_range(""), "Bad index" ));
  EXPECT_TRUE(Expect_Throw(cdi, AtFuncConst, di.size()+1000 , std::out_of_range(""), "Bad index" ));
  EXPECT_TRUE(Expect_Throw(cdi, AtFuncConst, -1             , std::out_of_range(""), "Bad index" ));
  EXPECT_TRUE(Expect_Throw(cdi, AtFuncConst, -1000          , std::out_of_range(""), "Bad index" ));
}

TEST (At, AfterUpdate) {
  const int n = 142; 
  const int k = 55; 
  const int j = 66;
  DEQ<int> di; 

  static_assert( k + j <= n, "[k, k+j-1] shoulld be inside [0, n-1]"); 
  for (int i = 0; i < n; i++) {
      di.push_back( i * i); 
  }
  ASSERT_EQ(n, di.size()); 
  for (int i = k; i < k + j; i++) {
      di.at(i) = di.at(i) + 1000;
  }
  for (int i = 0; i < n; i++) {
      if (i >= k && i < k + j) {
        ASSERT_EQ(i*i + 1000, di.at(i));
      } else {
        ASSERT_EQ(i*i, di.at(i));
      }
  }
}


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}