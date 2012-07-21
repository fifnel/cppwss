//
// HttpHeader Packet Parser
// Copyright (c) 2012 fifnel. All rights reserved.
//

#include "http_header_packet_parser.h"

#include <map>
#include <boost/algorithm/string.hpp>
#include <boost/regex.hpp>
#include <boost/foreach.hpp>

using namespace std;

namespace wss {

    // コンストラクタ
    HttpHeaderPacketParser::HttpHeaderPacketParser(Connection& connection,
                               size_t buffer_capacity)
        : PacketParser(connection, buffer_capacity)
    {
    }

    // コンストラクタ
    HttpHeaderPacketParser::HttpHeaderPacketParser(PacketParser *copy_source)
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

        { // debug log
            cout << packet_string_ << endl;
            cout << "-----------" << endl;
        }

        typedef map<string,string> string_pair_map;
        string_pair_map http_req_header;

        vector<string> packet_lines;
        boost::split(packet_lines, packet_string_, boost::is_any_of("\r\n"));

        BOOST_FOREACH(string &line, packet_lines) {
            boost::smatch m;
            static const boost::regex e("^(.+?)\\s*\\:\\s*(.+)$");
            if (regex_search(line, m, e)) {
                { // debug log
                    for (int i=0; i<m.size(); i++ ) {
                        cout << i << ":" << m[i] << endl;
                    }
                }
                if (m.size() == 3) {
                    http_req_header.insert(string_pair_map::value_type(m[1], m[2]));
                }
            }
            { // debug log
                cout << "-----------" << endl;
            }
        }

        { // debug log
            cout << "key:" << http_req_header["Sec-WebSocket-Key"] << endl;
        }
    }

} // namespace wss

