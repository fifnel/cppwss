//
// Web Socket Server
// Copyright (c) 2012 fifnel. All rights reserved.
//

#include "websocket_parser.h"

#include "websocket_frame.h"

#include <string>

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
        WebSocketFrame frame;
        if (frame.parsePacket(buffer_)) {
            string payload;
            payload.append(frame.getPayload().begin(), frame.getPayload().end());
            cout << "succeeded : " << payload << endl;
        } else {
            cout << "failure" << endl;
        }
        buffer_.clear();

        connection_.write("\x81\x05Hello", 7);
    }

} // namespace wss

