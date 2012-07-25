//
// HttpHeader Packet Parser Test
// Copyright (c) 2012 fifnel. All rights reserved.
//
#ifdef ENABLE_UNIT_TEST

#include "http_header_packet_parser.h"

#include "connection.h"
#include "connection_manager.h"

#include <boost/test/unit_test.hpp>

using namespace std;
using namespace boost::unit_test_framework;


namespace wss {

    void HttpHeaderPacketParser::unit_test()
    {
        int request_num = 0;
        string http_request;
        http_request.append("GET /wstest HTTP/1.1\r\n");
        http_request.append("Host: localhost:9000\r\n");request_num++;
        http_request.append("User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.7; rv:14.0) Gecko/20100101 Firefox/14.0.1\r\n");request_num++;
        http_request.append("Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\n");request_num++;
        http_request.append("Accept-Language: ja,en-us;q=0.7,en;q=0.3\r\n");request_num++;
        http_request.append("Accept-Encoding: gzip, deflate\r\n");request_num++;
        http_request.append("Connection: keep-alive, Upgrade\r\n");request_num++;
        http_request.append("Sec-WebSocket-Version: 13\r\n");request_num++;
        http_request.append("Origin: null\r\n");request_num++;
        http_request.append("Sec-WebSocket-Key: sw1dElTGtD8sVkj4Dp0+XQ==\r\n");request_num++;
        http_request.append("Pragma: no-cache\r\n");request_num++;
        http_request.append("Cache-Control: no-cache\r\n");request_num++;
        http_request.append("Upgrade: websocket\r\n");request_num++;
        http_request.append("\r\n");

        asio::io_service dummy_io_service;
        ConnectionManager dummy_connection_manager;
        Connection dummy_connection(dummy_io_service, dummy_connection_manager);

        HttpHeaderPacketParser parser(dummy_connection, 200);

        parser.appendPacket(http_request.c_str(), http_request.length());
        BOOST_CHECK_EQUAL(http_request.length(), parser.buffer_.size());

        parser.parse();
        BOOST_CHECK_EQUAL(request_num, parser.http_request_header_.size());
        BOOST_CHECK_EQUAL(parser.http_request_header_["Host"], "localhost:9000");
        BOOST_CHECK_EQUAL(parser.http_request_header_["Sec-WebSocket-Key"], "sw1dElTGtD8sVkj4Dp0+XQ==");
        BOOST_CHECK_EQUAL(parser.http_request_header_["Upgrade"], "websocket");
    }

} // namespace wss

#endif

