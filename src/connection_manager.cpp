//
// Connection Manager
// Copyright (c) 2012 fifnel. All rights reserved.
//

#include "connection_manager.h"

#include "connection.h"

#include <algorithm>
#include <boost/bind.hpp>

namespace wss
{
    // コンストラクタ
    ConnectionManager::ConnectionManager()
    {
    }

    // デストラクタ
    ConnectionManager::~ConnectionManager()
    {
    }

    // 開始
    void ConnectionManager::start(ConnectionPtr connection)
    {
        connections_.insert(connection);
        connection->start();
    }

    // 停止
    void ConnectionManager::stop(ConnectionPtr connection)
    {
        connections_.erase(connection);
        connection->stop();
    }

    // 全停止
    void ConnectionManager::stop_all()
    {
        for_each(
                connections_.begin(),
                connections_.end(),
                boost::bind(&Connection::stop, _1) );
        connections_.clear();
    }

} // namespace wss

