//
// Packet Parser
// Copyright (c) 2012 fifnel. All rights reserved.
//

#include "packet_parser.h"

namespace wss {

    // コンストラクタ
    PacketParser::PacketParser(Connection& connection,
                               size_t buffer_capacity)
        : connection_(connection)
        , buffer_(buffer_capacity)
    {
    }

    // デストラクタ
    PacketParser::~PacketParser()
    {
    }

    // パケットの追加
    void PacketParser::appendPacket(char *buffer, size_t size)
    {
        buffer_.insert(buffer_.end(), buffer, buffer+size);
    }

} // namespace wss

