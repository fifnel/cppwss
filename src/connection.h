//
// Connection
// Copyright (c) 2012 fifnel. All rights reserved.
//

#ifndef __CPPWSS_CONNECTION_H__
#define __CPPWSS_CONNECTION_H__

#include <boost/enable_shared_from_this.hpp>
#include <boost/noncopyable.hpp>
#include <boost/asio.hpp>

using namespace std;
namespace asio = boost::asio;

namespace wss {

    class ConnectionManager;

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
    };

    typedef boost::shared_ptr<Connection> ConnectionPtr;

} // namespace wss

#endif

