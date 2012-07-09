//
//  WebSocketServer.h
//  CppWebSocket
//
//  Created by fifnel on 2012/04/18.
//  Copyright (c) 2012年 fifnel. All rights reserved.
//

#ifndef CppWebSocket_WebSocketServer_h
#define CppWebSocket_WebSocketServer_h

#include <boost/asio.hpp>
#include <boost/noncopyable.hpp>

#include "connection.h"
#include "connection_manager.h"

using namespace std;
namespace asio = boost::asio;

namespace WebSocket {

    /**
     WebSocketサーバー
     */
    class Server
        : private boost::noncopyable
    {
    public:
        
        // コンストラクタ
        explicit Server(const string &address, const string &port);
        
        
        // デストラクタ
        virtual ~Server();
        
        // 開始
        void run();
        
    private:
        
        // accept開始
        void start_accept();
        
        // acceptハンドラ
        void handle_accept(const boost::system::error_code& error);
        
        // stopハンドラ
        void handle_stop(const boost::system::error_code &error, int signal_number);
        
        
    private:
        std::string address_;
        std::string port_;
        
        asio::io_service io_service_;
        asio::signal_set signals_;
        asio::ip::tcp::acceptor accepter_;
        ConnectionPtr new_connection_;
        ConnectionManager connection_manager_;
    };
    
} // namespace WebSocket


#endif
