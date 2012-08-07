//
// HttpHeader Packet Parser
// Copyright (c) 2012 fifnel. All rights reserved.
//

#include "http_header_packet_parser.h"

#include "web_socket_parser.h"

#include <map>
#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <boost/regex.hpp>
#include <boost/foreach.hpp>
#include <boost/archive/iterators/base64_from_binary.hpp>
#include <boost/archive/iterators/transform_width.hpp>
#include <cryptopp/sha.h>

using namespace std;
using namespace boost::archive::iterators;

#define HANDSHAKE_MAGIC_STRING "258EAFA5-E914-47DA-95CA-C5AB0DC85B11"

namespace wss {

    // コンストラクタ
    HttpHeaderPacketParser::HttpHeaderPacketParser(Connection& connection,
                               size_t buffer_capacity)
        : PacketParser(connection, buffer_capacity)
    {
    }

    // コンストラクタ
    HttpHeaderPacketParser::HttpHeaderPacketParser(const PacketParser *copy_source)
        : PacketParser(copy_source)
    {
    }

    // デストラクタ
    HttpHeaderPacketParser::~HttpHeaderPacketParser()
    {
    }

    // パケットのパース処理
    void HttpHeaderPacketParser::parse()
    {
        // パケットバッファを文字列に変換
        packet_string_.append(buffer_.begin(), buffer_.end());
        vector<char>().swap(buffer_);

        vector<string> packet_lines;
        boost::split(packet_lines, packet_string_, boost::is_any_of("\r\n"));

        BOOST_FOREACH(string &line, packet_lines) {
            boost::smatch m;
            static const boost::regex e("^(.+?)\\s*\\:\\s*(.+)$");
            if (regex_search(line, m, e)) {
                if (m.size() == 3) {
                    string http_header_field = m[1];
                    std::transform(http_header_field.begin(), http_header_field.end(), http_header_field.begin(), ::toupper);
                    http_request_header_.insert(map<string,string>::value_type(http_header_field, m[2]));
                }
            }
        }

        upgrade();
    }

    // Upgrade処理
    void HttpHeaderPacketParser::upgrade()
    {
        if (
                   http_request_header_["UPGRADE"] != "websocket"
                || http_request_header_["SEC-WEBSOCKET-VERSION"] != "13"
           ) {
            return;
        }

        string encoded_text =
            toBase64( toSHA1( http_request_header_["SEC-WEBSOCKET-KEY"]+HANDSHAKE_MAGIC_STRING ) );

        string http_response_header;

        http_response_header += "HTTP/1.1 101 Switching Protocols\r\n";
        http_response_header += "Upgrade: websocket\r\n";
        http_response_header += "Connection: Upgrade\r\n";
        http_response_header += "Sec-WebSocket-Accept: "+encoded_text+"\r\n";
        http_response_header += "\r\n\r\n";

        connection_.write(http_response_header.c_str(), http_response_header.length());

        connection_.switch_packet_parser(boost::shared_ptr<PacketParser>(new WebSocketParser(this)));

        cout << http_response_header << endl;
    }

    // バイナリ配列をBase64エンコードした文字列に変換する
    string HttpHeaderPacketParser::toBase64(const vector<byte>& source)
    {
        typedef base64_from_binary<transform_width<vector<byte>::const_iterator,6,8> > base64;

        string encoded_text(
                base64(source.begin()),
                base64(source.end())
                );
        int padding_count = 4-encoded_text.length()%4;
        for (int i=0; i<padding_count; i++) {
            encoded_text += '=';
        }

        return encoded_text;
    }

    // 文字列をSHA1変換する
    vector<byte> HttpHeaderPacketParser::toSHA1(const string& source)
    {
        byte buf[CryptoPP::SHA1::DIGESTSIZE];

        CryptoPP::SHA1().CalculateDigest( buf, reinterpret_cast<const byte*>(source.c_str()), source.length());

        vector<byte> encoded_bytes;
        encoded_bytes.assign(buf, buf+sizeof(buf));

        return encoded_bytes;
    }

} // namespace wss

