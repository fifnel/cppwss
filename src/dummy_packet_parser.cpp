//
// Dummy Packet Parser
// Copyright (c) 2012 fifnel. All rights reserved.
//

#include "dummy_packet_parser.h"

#include "http_header_packet_parser.h"

using namespace std;

namespace wss {

    // コンストラクタ
    DummyPacketParser::DummyPacketParser(Connection& connection,
                               size_t buffer_capacity)
        : PacketParser(connection, buffer_capacity)
    {
    }

    // コンストラクタ
    DummyPacketParser::DummyPacketParser(PacketParser *copy_source)
        : PacketParser(copy_source)
    {
    }

    // デストラクタ
    DummyPacketParser::~DummyPacketParser()
    {
    }

    // パケットのパース処理
    void DummyPacketParser::parse()
    {
        cout << "switch!!" << endl;
        connection_.switch_packet_parser(boost::shared_ptr<PacketParser>(new HttpHeaderPacketParser(this)));
    }

} // namespace wss

