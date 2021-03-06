//
// WebSocket Parser
// Copyright (c) 2012 fifnel. All rights reserved.
//

#ifndef __CPPWSS_WEBSOCKET_PARSER_H__
#define __CPPWSS_WEBSOCKET_PARSER_H__

#include "connection.h"
#include "packet_parser.h"

using namespace std;

namespace wss {

    class WebSocketParser
        : public PacketParser
    {
    public:
        // コンストラクタ
        explicit WebSocketParser(Connection& connection,
                size_t buffer_capacity = 8192);

        // コンストラクタ
        explicit WebSocketParser(const PacketParser *copy_source);

        // デストラクタ
        virtual ~WebSocketParser();

        // パケットのパース処理
        virtual void parse();

    private:
        // WebSocket Frameのパース
        bool parse_websocket_frame(const vector<char>& payload_data_);

        unsigned char opcode_;
        vector<char> payload_data_;

#ifdef ENABLE_UNIT_TEST
    public:
        static void unit_test();
#endif
    };

} // namespace wss

#endif

