//
//  ConnectionManager.h
//  CppWebSocket
//
//  Created by fifnel on 2012/04/19.
//  Copyright (c) 2012年 fifnel. All rights reserved.
//

#ifndef __ConnectionManager_H_
#define __ConnectionManager_H_

#include <set>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>

#include "connection.h"

using namespace std;
namespace asio = boost::asio;

namespace WebSocket
{
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

} // namespace WebSocket

#endif //__ConnectionManager_H_
