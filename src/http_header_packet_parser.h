//
// HTTP Header Packet Parser
// Copyright (c) 2012 fifnel. All rights reserved.
//

#ifndef __CPPWSS_HTTP_HADER_PACKET_PARSER_H__
#define __CPPWSS_HTTP_HADER_PACKET_PARSER_H__

#include "connection.h"
#include "packet_parser.h"

using namespace std;

namespace wss {

    class HttpHeaderPacketParser
        : public PacketParser
    {
    public:
        // コンストラクタ
        explicit HttpHeaderPacketParser(Connection& connection,
                size_t buffer_capacity = 8192);

        // コンストラクタ
        explicit HttpHeaderPacketParser(const PacketParser *copy_source);

        // デストラクタ
        virtual ~HttpHeaderPacketParser();

        // パケットのパース処理
        virtual void parse();

    private:
        string packet_string_;

        map<string,string> http_request_header_;

#ifdef ENABLE_UNIT_TEST
    public:
        static void unit_test();
#endif
    };

} // namespace wss

#endif


