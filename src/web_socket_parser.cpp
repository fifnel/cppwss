//
// Web Socket Server
// Copyright (c) 2012 fifnel. All rights reserved.
//

#include "web_socket_parser.h"

using namespace std;

namespace wss {

    // コンストラクタ
    WebSocketParser::WebSocketParser(Connection& connection,
                               size_t buffer_capacity)
        : PacketParser(connection, buffer_capacity)
    {
    }

    // コンストラクタ
    WebSocketParser::WebSocketParser(const PacketParser *copy_source)
        : PacketParser(copy_source)
    {
    }

    // デストラクタ
    WebSocketParser::~WebSocketParser()
    {
    }

    // パケットのパース処理
    void WebSocketParser::parse()
    {
        // パケットバッファを文字列に変換
        packet_string_.append(buffer_.begin(), buffer_.end());
        vector<char>().swap(buffer_);

        cout << "websokcetparser" << endl;
    }

} // namespace wss

