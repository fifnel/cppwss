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
    {
        buffer_.reserve(buffer_capacity);
    }

    // コンストラクタ
    PacketParser::PacketParser(const PacketParser *copy_source)
        : connection_(copy_source->connection_)
    {
        buffer_.assign(copy_source->buffer_.begin(), copy_source->buffer_.end());
    }

    // デストラクタ
    PacketParser::~PacketParser()
    {
    }

    // パケットの追加
    void PacketParser::appendPacket(const char *buffer, size_t size)
    {
        buffer_.insert(buffer_.end(), buffer, buffer+size);
    }

} // namespace wss

