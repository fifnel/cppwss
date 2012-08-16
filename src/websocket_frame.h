//
// WebSocket Frame
// Copyright (c) 2012 fifnel. All rights reserved.
//

#ifndef __CPPWSS_WEBSOCKET_FRAME_H__
#define __CPPWSS_WEBSOCKET_FRAME_H__

#include <vector>

using namespace std;

namespace wss {

    class WebSocketFrame
    {
    public:
        // コンストラクタ
        WebSocketFrame();

        // デストラクタ
        virtual ~WebSocketFrame();

        // パケットの読み込み
        bool parsePacket(const vector<char>& buffer);

        // 直前に読み込んだパケットのopcode取得
        unsigned char getOpcode();

        // payloadの取得
        const vector<char> &getPayload();

    protected:

        bool fin_;
        char opcode_;
        vector<char> payload_data_;
    };

} // namespace wss

#endif
