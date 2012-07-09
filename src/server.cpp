//
//  Server.c
//  CppWebSocket
//
//  Created by fifnel on 2012/04/18.
//  Copyright (c) 2012年 fifnel. All rights reserved.
//

#include "server.h"

#include <boost/shared_ptr.hpp>
#include <boost/bind.hpp>
#include <boost/asio.hpp>

// TODO: handle_stopの実装

namespace WebSocket {

    // コンストラクタ
    Server::Server(const string &address, const string &port)
        : address_(address)
        , port_(port)
        , io_service_()
        , signals_(io_service_)
        , accepter_(io_service_)
        , connection_manager_()
        , new_connection_()
    {
        signals_.add(SIGINT);
        signals_.add(SIGTERM);
#if defined(SIGQUIT)
        signals_.add(SIGQUIT);
#endif // defined(SIGQUIT)
        signals_.async_wait(boost::bind(&Server::handle_stop, this, _1, _2));
        
        asio::ip::tcp::resolver resolver(io_service_);
        asio::ip::tcp::resolver::query query(address_, port_);
        asio::ip::tcp::endpoint endpoint = *resolver.resolve(query);
        
        accepter_.open(endpoint.protocol());
        accepter_.set_option(asio::ip::tcp::acceptor::reuse_address(true));
        accepter_.bind(endpoint);
        accepter_.listen();
        
        start_accept();
    }
    
    // デストラクタ
    Server::~Server()
    {
    }
    
    // 開始
    void Server::run()
    {
        io_service_.run();
    }
        
    // accept開始
    void Server::start_accept()
    {
        new_connection_.reset(new Connection(io_service_, connection_manager_));
        accepter_.async_accept(new_connection_->socket(), boost::bind(&Server::handle_accept, this, asio::placeholders::error));
    }
    
    // acceptハンドラ
    void Server::handle_accept(const boost::system::error_code& error)
    {
        cout << "accept" << endl;
        if (!accepter_.is_open()) {
            return;
        }
        if (!error) {
            connection_manager_.start(new_connection_);
        }
        
        start_accept();
    }
    
    // stopハンドラ
    void Server::handle_stop(const boost::system::error_code &error, int signal_number)
    {
        accepter_.close();
        connection_manager_.stop_all();
    }


} // namespace WebSocket
