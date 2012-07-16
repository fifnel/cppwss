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
        cout << "constor" << endl;
    }

    // コンストラクタ
    DummyPacketParser::DummyPacketParser(PacketParser *copy_source)
        : PacketParser(copy_source)
    {
        cout << "destor" << endl;
    }

    // デストラクタ
    DummyPacketParser::~DummyPacketParser()
    {
    }

    // パケットのパース処理
    void DummyPacketParser::parse()
    {
        // パケットバッファを文字列に変換
        packet_string.append(buffer_.begin(), buffer_.end());
        vector<char>().swap(buffer_);

        // dummy
        const char *hoge = "hoge";
        connection_.write(hoge, 4);


        cout << packet_string << endl;

        connection_.switch_packet_parser(boost::shared_ptr<PacketParser>(new DummyPacketParser(this)));
    }

} // namespace wss

