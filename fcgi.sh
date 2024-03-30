#!/bin/bash

case $1 in
    start)
        START=1
        STOP=0
        ;;
    stop)
        START=0
        STOP=1
        ;;
    "")
        START=0
        STOP=1
        ;;
    *)
        START=0
        STOP=0
        ;;
esac

if [ "$STOP" -eq 1 ];then
    #登录
    kill -9 $(ps aux | grep "./bin/login" | grep -v grep | awk '{print $2}') > /dev/null 2>&1
    echo "FCGI 程序已经成功关闭, bye-bye ..."
fi

# ******************************* 重新启动CGI进程 ******************************* 
if [ "$START" -eq 1 ];then
    echo -n "登录:"
    sudo spwan-fcgi -a 127.0.0.1 -p 10000 -f ./bin/login
fi