//
// Connection Manager
// Copyright (c) 2012 fifnel. All rights reserved.
//

#ifndef __CPPWSS_CONNECTION_MANAGER_H__
#define __CPPWSS_CONNECTION_MANAGER_H__

#include "connection.h"

#include <set>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>

using namespace std;
namespace asio = boost::asio;

namespace wss {

    class Connection;

    class ConnectionManager
        : public boost::noncopyable
    {
    public:
        // コンストラクタ
        ConnectionManager();

        // デストラクタ
        virtual ~ConnectionManager();

        // 開始
        void start(ConnectionPtr connection);

        // 停止
        void stop(ConnectionPtr connection);

        // 全停止
        void stop_all();

    private:
        set<ConnectionPtr> connections_;
    };

} // namespace wss

#endif

