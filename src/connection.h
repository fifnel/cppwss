//
//  Connection.h
//  CppWebSocket
//
//  Created by fifnel on 2012/04/18.
//  Copyright (c) 2012年 fifnel. All rights reserved.
//

#ifndef CppWebSocket_Connection_h
#define CppWebSocket_Connection_h

#include <boost/enable_shared_from_this.hpp>
#include <boost/noncopyable.hpp>
#include <boost/asio.hpp>

using namespace std;
namespace asio = boost::asio;

namespace WebSocket {
    
    class ConnectionManager;

    class Connection
        : public boost::enable_shared_from_this<Connection>
        , private boost::noncopyable
    {
    public:
        // コンストラクタ
        explicit Connection(asio::io_service& io_service, ConnectionManager& connection_manager);

        // デストラクタ
        virtual ~Connection();

        // 開始
        void start();

        // 停止
        void stop();
        
        // ソケットの取得
        asio::ip::tcp::socket& socket();

    private:
        // readハンドラ
        void handle_read(const boost::system::error_code& error, std::size_t bytes_transferred);

        // writeハンドラ
        void handle_write(const boost::system::error_code& error, std::size_t bytes_transferred);
        
        // コネクションマネージャ
        ConnectionManager& connection_manager_;
        
        // ソケット
        asio::ip::tcp::socket socket_;
        
        // 受信バッファ
        boost::array<char, 8192> buffer_;
    };
    
    typedef boost::shared_ptr<Connection> ConnectionPtr;

} // namespace WebSocket

#endif
