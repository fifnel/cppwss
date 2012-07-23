//
// HttpHeader Packet Parser Test
// Copyright (c) 2012 fifnel. All rights reserved.
//
#ifdef ENABLE_UNIT_TEST

#include "http_header_packet_parser.h"

#include <boost/test/unit_test.hpp>

using namespace std;
using namespace boost::unit_test_framework;


namespace wss {

    void HttpHeaderPacketParser::unit_test()
    {
        /*
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
        */
        BOOST_CHECK(2==4);
        BOOST_TEST_CHECKPOINT("check!");
        char *hoge = 0;
        *hoge = 100;
        BOOST_FAIL("failure");
    }


} // namespace wss

#endif

