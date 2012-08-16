//
// Connection
// Copyright (c) 2012 fifnel. All rights reserved.
//

#ifndef __CPPWSS_CONNECTION_H__
#define __CPPWSS_CONNECTION_H__

#include <boost/enable_shared_from_this.hpp>
#include <boost/noncopyable.hpp>
#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>

using namespace std;
namespace asio = boost::asio;

namespace wss {

    class ConnectionManager;
    class PacketParser;
    typedef boost::shared_ptr<PacketParser> PacketParserPtr;

    class Connection
        : public  boost::enable_shared_from_this<Connection>
        , private boost::noncopyable
    {
    public:
        // コンストラクタ
        explicit Connection(asio::io_service& io_service,
                            ConnectionManager& connection_manager);

        // デストラクタ
        virtual ~Connection();

        // 開始
        void start();

        // 停止
        void stop();

        // ソケットの取得
        asio::ip::tcp::socket& socket();

        // パケットの書き込み
        void write(const char *buffer, size_t size);

        // パケットパーサーの切り替え
        void switch_packet_parser(const boost::shared_ptr<PacketParser> &packet_parser);

    private:
        // 読み込み時に呼ばれる
        void handle_read(const boost::system::error_code& error, std::size_t bytes_transferred);

        // 書き込み時に呼ばれる
        void handle_write(const boost::system::error_code& error, std::size_t bytes_transferred);

        // コネクションマネージャ
        ConnectionManager& connection_manager_;

        // ソケット
        asio::ip::tcp::socket socket_;

        // 受信バッファ
        boost::array<char, 8192> buffer_;

        // 受信バッファのパーサ
        PacketParserPtr packet_parser_;

        // 切り替え待機中の受信バッファのパーサ
        PacketParserPtr next_packet_parser_;

#ifdef ENABLE_UNIT_TEST
    public:
        static void unit_test();
#endif
    };

    typedef boost::shared_ptr<Connection> ConnectionPtr;

} // namespace wss

#endif

