//
// Initialize Unit Test Suite
// Copyright (c) 2012 fifnel. All rights reserved.
//
#ifdef ENABLE_UNIT_TEST

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE cppwss

#include "server.h"
#include "connection.h"
#include "connection_manager.h"
#include "dummy_packet_parser.h"
#include "websocket_parser.h"
#include "http_header_packet_parser.h"
#include "websocket_frame.h"

#include <boost/test/unit_test.hpp>

using namespace std;
using namespace boost::unit_test_framework;

BOOST_AUTO_TEST_CASE(server_base_classes) {

    wss::Server::unit_test();
    wss::Connection::unit_test();
    wss::ConnectionManager::unit_test();

}

BOOST_AUTO_TEST_CASE(websocket) {

    wss::WebSocketParser::unit_test();
    wss::HttpHeaderPacketParser::unit_test();
    wss::WebSocketFrame::unit_test();

}

BOOST_AUTO_TEST_CASE(dummy) {

    wss::DummyPacketParser::unit_test();

}

#endif


