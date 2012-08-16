//
// TCP Server
// Copyright (c) 2012 fifnel. All rights reserved.
//

#ifndef __CPPWSS_SERVER_H__
#define __CPPWSS_SERVER_H__

#include <boost/asio.hpp>
#include <boost/noncopyable.hpp>

#include "connection.h"
#include "connection_manager.h"

using namespace std;
namespace asio = boost::asio;

namespace wss {

    class Server : private boost::noncopyable
    {
    public:

        // コンストラクタ
        explicit Server(const string &address, const string &port);

        // デストラクタ
        virtual ~Server();

        // サーバー処理開始
        void run();

    private:

        // accept開始
        void start_accept();

        // accept時に呼ばれる
        void handle_accept(const boost::system::error_code& error);

        // 停止時に呼ばれる
        void handle_stop(const boost::system::error_code &error, int signal_number);


    private:
        std::string address_;
        std::string port_;

        asio::io_service          io_service_;
        asio::signal_set          signals_;
        asio::ip::tcp::acceptor   accepter_;

        ConnectionPtr new_connection_;
        ConnectionManager connection_manager_;

#ifdef ENABLE_UNIT_TEST
    public:
        static void unit_test();
#endif
    };

} // namespace wss

#endif
