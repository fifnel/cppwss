//
// Packet Parser
// Copyright (c) 2012 fifnel. All rights reserved.
//

#ifndef __CPPWSS_PACKET_PARSER_H__
#define __CPPWSS_PACKET_PARSER_H__

#include "connection.h"

using namespace std;

namespace wss {

    class PacketParser
        : private boost::noncopyable
    {
    public:
        // コンストラクタ
        explicit PacketParser(ConnectionPtr connection,
                              size_t buffer_capacity = 8192);

        // デストラクタ
        virtual ~PacketParser();

        // パケットの追加
        void appendPacket(char *buffer, size_t size);

        // パケットのパース処理
        virtual void parse() = 0;

    protected:
        vector<char> buffer_;
        ConnectionPtr connection_;
    };

} // namespace wss

#endif

