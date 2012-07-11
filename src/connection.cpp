//
// Connection
// Copyright (c) 2012 fifnel. All rights reserved.
//

#include "connection.h"

#include "connection_manager.h"

#include <boost/bind.hpp>

namespace wss {

    // コンストラクタ
    Connection::Connection(asio::io_service& io_service, ConnectionManager& connection_manager)
        : connection_manager_(connection_manager)
        , socket_(io_service)
    {
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

    // readハンドラ
    void Connection::handle_read(const boost::system::error_code& error, std::size_t bytes_transferred)
    {
        // TODO:未実装
        string buf(buffer_.c_array(), bytes_transferred);
        cout << "[" << buf << "]" << endl;

        socket_.async_write_some(asio::buffer("hoge"),
                boost::bind(&Connection::handle_write,
                    shared_from_this(),
                    asio::placeholders::error,
                    asio::placeholders::bytes_transferred));

        socket_.async_read_some( asio::buffer(buffer_),
                boost::bind(&Connection::handle_read,
                    shared_from_this(),
                    asio::placeholders::error,
                    asio::placeholders::bytes_transferred) );

        // エラー発生時はコレを呼ぶ
        //        connection_manager_.stop(shared_from_this());
    }

    // writeハンドラ
    void Connection::handle_write(const boost::system::error_code& error, std::size_t bytes_transferred)
    {
        cout << "write" << endl;
        // TODO:未実装

        // エラー発生時はコレを呼ぶ
        //        connection_manager_.stop(shared_from_this());
    }

} // namespace wss

