//
// Dummy Packet Parser
// Copyright (c) 2012 fifnel. All rights reserved.
//

#ifndef __CPPWSS_DUMMY_PACKET_PARSER_H__
#define __CPPWSS_DUMMY_PACKET_PARSER_H__

#include "connection.h"
#include "packet_parser.h"

#include <boost/noncopyable.hpp>

using namespace std;

namespace wss {

    class DummyPacketParser
        : public PacketParser
    {
    public:
        // コンストラクタ
        explicit DummyPacketParser(Connection& connection,
                                   size_t buffer_capacity = 8192);

        // デストラクタ
        virtual ~DummyPacketParser();

        // パケットのパース処理
        virtual void parse();

    private:
        string packet_string;
    };

} // namespace wss

#endif

