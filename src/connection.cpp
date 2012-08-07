//
// Connection
// Copyright (c) 2012 fifnel. All rights reserved.
//

#include "connection.h"

#include "connection_manager.h"
#include "packet_parser.h"
#include "http_header_packet_parser.h"

#include <boost/bind.hpp>

namespace wss {

    // コンストラクタ
    Connection::Connection(asio::io_service& io_service, ConnectionManager& connection_manager)
        : connection_manager_(connection_manager)
        , socket_(io_service)
    {
        packet_parser_ = PacketParserPtr(new HttpHeaderPacketParser(*this));
    }

    // デストラクタ
    Connection::~Connection()
    {
    }

    // 開始
    void Connection::start()
    {
        socket_.async_read_some( asio::buffer(buffer_),
                boost::bind(&Connection::handle_read,
                    shared_from_this(),
                    asio::placeholders::error,
                    asio::placeholders::bytes_transferred) );
    }

    // 停止
    void Connection::stop()
    {
        socket_.close();
    }

    // ソケットの取得
    asio::ip::tcp::socket& Connection::socket()
    {
        return socket_;
    }

    // パケットの書き込み
    void Connection::write(const char *buffer, size_t size)
    {
        socket_.async_write_some(asio::buffer(buffer, size),
                boost::bind(&Connection::handle_write,
                    shared_from_this(),
                    asio::placeholders::error,
                    asio::placeholders::bytes_transferred));
    }

    // パケットパーサーの切り替え
    void Connection::switch_packet_parser(const boost::shared_ptr<PacketParser> &packet_parser)
    {
        if (packet_parser == packet_parser_) {
            next_packet_parser_.reset();
            return;
        }
        if (packet_parser == packet_parser_) {
            return;
        }

        next_packet_parser_ = packet_parser;
    }

    // 読み込み時に呼ばれる
    void Connection::handle_read(const boost::system::error_code& error, std::size_t bytes_transferred)
    {
        if (error)  {
            connection_manager_.stop(shared_from_this());
            return;
        }

        if (bytes_transferred > 0) {
            packet_parser_->appendPacket(buffer_.c_array(), bytes_transferred);
            packet_parser_->parse();
        }

        if (next_packet_parser_.get()) {
            packet_parser_ = next_packet_parser_;
            next_packet_parser_.reset();

            packet_parser_->parse(); // ここで一度呼ばないと次に何かパケットが送られてくるまで呼ばれないので
        }

        // 次の読み込み
        socket_.async_read_some( asio::buffer(buffer_),
                boost::bind(&Connection::handle_read,
                    shared_from_this(),
                    asio::placeholders::error,
                    asio::placeholders::bytes_transferred) );

    }

    // 書き込み時に呼ばれる
    void Connection::handle_write(const boost::system::error_code& error, std::size_t bytes_transferred)
    {
        if (error)  {
            connection_manager_.stop(shared_from_this());
            return;
        }
    }

} // namespace wss

