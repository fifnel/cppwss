//
// Initialize Unit Test Suite
// Copyright (c) 2012 fifnel. All rights reserved.
//
#ifdef ENABLE_UNIT_TEST

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE cppwss

#include "http_header_packet_parser.h"

#include <boost/test/unit_test.hpp>

using namespace std;
using namespace boost::unit_test_framework;

BOOST_AUTO_TEST_CASE(unit_test) {

    wss::HttpHeaderPacketParser::unit_test();

}

#endif


