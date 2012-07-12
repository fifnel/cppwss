//
// Dummy Packet Parser
// Copyright (c) 2012 fifnel. All rights reserved.
//

#include "dummy_packet_parser.h"

using namespace std;

namespace wss {

    // コンストラクタ
    DummyPacketParser::DummyPacketParser(Connection& connection,
                               size_t buffer_capacity)
        : PacketParser(connection, buffer_capacity)
    {
    }

    // デストラクタ
    DummyPacketParser::~DummyPacketParser()
    {
    }

    // パケットのパース処理
    void DummyPacketParser::parse()
    {
        // dummy
        const char *hoge = "hoge";
        connection_.write(hoge, 4);
    }

} // namespace wss

