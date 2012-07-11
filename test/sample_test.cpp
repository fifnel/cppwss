#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE cppwss

#include "../src/helloworld.h"
#include <boost/test/unit_test.hpp>

using namespace boost::unit_test_framework;

BOOST_AUTO_TEST_CASE(cppwss) {
    CHelloWorld hello(3);
    
    hello.print();

    BOOST_WARN(false);
}


BOOST_AUTO_TEST_CASE(cppwss2) {
    BOOST_CHECK(2==4);
    BOOST_TEST_CHECKPOINT("check!");
    char *hoge = 0;
    *hoge = 100;
    BOOST_FAIL("failure");
}


