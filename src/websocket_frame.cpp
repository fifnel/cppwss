//
// WebSocket Frame
// Copyright (c) 2012 fifnel. All rights reserved.
//

#include "websocket_frame.h"

#include <iostream>

#define DEBUG_OUTPUT

using namespace std;

namespace wss {

    // コンストラクタ
    WebSocketFrame::WebSocketFrame()
        : fin_(false)
        , opcode_(0)
    {
    }

    // デストラクタ
    WebSocketFrame::~WebSocketFrame()
    {
    }

    // パケットの読み込み
    bool WebSocketFrame::parsePacket(const vector<char>& buffer)
    {
        int pos = 0;

        //----------------------------------------------
        bool fin    = false;
        char opcode = 0;
        {
            int len = 1;
            if (buffer.size() < pos+len) {
                return false;
            }

            unsigned char c = buffer[pos];
            fin    = (c >> 7 & 0x01) ? true : false;
            opcode = (c >> 0 & 0x07);
            pos += len;

#ifdef DEBUG_OUTPUT
            cout << "----------" << endl;
            cout << "FIN    : " << (c >> 7 & 0x01) << endl;
            cout << "RSV1   : " << (c >> 6 & 0x01) << endl;
            cout << "RSV2   : " << (c >> 5 & 0x01) << endl;
            cout << "RSV3   : " << (c >> 4 & 0x01) << endl;
            cout << "opcode : " << (c >> 0 & 0x07) << endl;
#endif
        }

        //----------------------------------------------
        char mask = 0;
        unsigned long long payload_len = 0;
        {
            int len = 1;
            if (buffer.size() < pos+len) {
                return false;
            }

            unsigned char c = buffer[pos];
            mask        = (c >> 7 & 0x01);
            payload_len = (c >> 0 & 0x7f);
            pos += len;

#ifdef DEBUG_OUTPUT
            cout << "----------" << endl;
            cout << "MASK        : " << (c >> 7 & 0x01) << endl;
            cout << "Payload len : " << (c >> 0 & 0x7f) << endl;
#endif
        }

        //----------------------------------------------
        if (payload_len == 126) {
            int len = 2;
            if (buffer.size() < pos+len) {
                return false;
            }
            payload_len = 0;
            payload_len |= (buffer[pos+0] << 8) & 0x0000ff00;
            payload_len |= (buffer[pos+1] << 0) & 0x000000ff;
            pos += len;

#ifdef DEBUG_OUTPUT
            cout << "----------" << endl;
            cout << "Payload len(16bit) : " << payload_len << endl;
#endif
        } else if (payload_len == 127) {
            int len = 4;
            if (buffer.size() < pos+len) {
                return false;
            }
            payload_len = 0;
            payload_len |= (buffer[pos+0] << 24) & 0xff000000;
            payload_len |= (buffer[pos+1] << 16) & 0x00ff0000;
            payload_len |= (buffer[pos+2] << 8)  & 0x0000ff00;
            payload_len |= (buffer[pos+3] << 0)  & 0x000000ff;
            pos += len;

#ifdef DEBUG_OUTPUT
            cout << "----------" << endl;
            cout << "Payload len(64bit) : " << payload_len << endl;
#endif
        }

        //----------------------------------------------
        unsigned char masking_key[4];
        if (mask == 1) {
            int len = 4;
            if (buffer.size() < pos+len) {
                return false;
            }
            masking_key[0] = buffer[pos+0];
            masking_key[1] = buffer[pos+1];
            masking_key[2] = buffer[pos+2];
            masking_key[3] = buffer[pos+3];
            pos += len;

#ifdef DEBUG_OUTPUT
            cout << "----------" << endl;
            printf("Masking-key : %02x %02x %02x %02x\n", masking_key[0], masking_key[1], masking_key[2], masking_key[3]);
#endif
        }

        int mask_index = 0;
        while (buffer.size() > pos) {
            char payload_data;
            payload_data = buffer[pos] ^ masking_key[mask_index];

            payload_data_.push_back(payload_data);

            mask_index = (mask_index+1)&3;
            pos++;

#ifdef DEBUG_OUTPUT
            printf("Payload Data %04d : %02x(%c)\n", pos, payload_data, payload_data);
#endif
        }

        fin_ = fin;
        opcode_ = opcode;

        return true;
     }

    // 直前に読み込んだパケットのopcode取得
    unsigned char WebSocketFrame::getOpcode()
    {
        return opcode_;
    }

    // payloadの取得
    const vector<char> &WebSocketFrame::getPayload()
    {
        return payload_data_;
    }

} // namespace wss

