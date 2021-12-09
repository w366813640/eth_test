/*
   服务器端程序
   接收客户端连接
   将客户端发送的数据写入记录文件中
   每个新连接都会创建新记录文件
*/

package main

import (
	"fmt"
	"io"
	"log"
	"net"
	"os"
	"strconv"
	"sync"
)

const (
	NETWORK string = "tcp"     //socket网络协议
	LADDR   string = ":8080"   //绑定的本机地址和端口
	LOGFILE string = "log.txt" //日子文件名
)

func main() {
	var mu sync.Mutex                                                       //创建锁,主要是防止协程将连接的传输写入同一个文件中
	var count int = 0                                                       //创建文件时区分文件用的
	f, err := os.OpenFile(LOGFILE, os.O_RDWR|os.O_APPEND|os.O_CREATE, 0666) //打开文件日志,没有就创建
	if err != nil {
		fmt.Printf("打开日志文件失败!error:%s\n", err)
		os.Exit(1)
	}
	defer f.Close()
	logger := log.New(f, "", 1)                 //创建日志对象
	listener, err := net.Listen(NETWORK, LADDR) //创建socket,绑定绑定端口,实现监听
	if err != nil {
		logger.Printf("监听端口失败!error:%s", err) //将错误写入日志文件中
		os.Exit(1)
	}
	defer listener.Close() //延迟关闭socket
	for {
		conn, err := listener.Accept() //创建连接

		if err != nil {
			logger.Printf("创建连接失败!error:err%s", err)
			os.Exit(1)
		}
		go connHandle(conn, logger, &count, mu) //创建协程处理连接
	}

}

func connHandle(conn net.Conn, logger *log.Logger, countPtr *int, mu sync.Mutex) {
	mu.Lock()
	defer mu.Unlock()  //实现协程并发安全,防止不同连接数据写入同一个记录文件中
	defer conn.Close() //延迟关闭连接
	*countPtr++
	fileName := "rev_data" + strconv.Itoa(*countPtr) + ".txt"
	f, err := os.OpenFile(fileName, os.O_RDWR|os.O_APPEND|os.O_CREATE, 0666) //创建并打开连接记录文件
	if err != nil {
		logger.Printf("打开记录文件失败!error:%s\n", err)
		return
	}
	defer f.Close()                     //关闭文件
	Raddr := conn.RemoteAddr().String() //客户端的IP和端口号
	f.WriteString("客户端:" + Raddr + "已连接 \n")
	var buf []byte = make([]byte, 4096)
	for {
		n, err := conn.Read(buf) //将客户端发送的数据写入buf中
		if err != nil {
			if err == io.EOF {
				f.WriteString("socket连接已关闭!\n")
				break
			} else {
				f.WriteString("写入数据失败!error:" + err.Error() + "\n")
				break
			}
		}
		f.WriteString(string(buf[:n]) + "\n") //将buf中的数据写入文件中
	}
}
