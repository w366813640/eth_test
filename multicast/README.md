# UDP Multicast Test
UDP Multicast Test是一个简单的UDP组播功能测试程序，旨在验证组播环境是否正确部署。

## 使用方式
首先获取代码后编译：

    git clone https://git.oschina.net/zyqhi/UDPMulticastTest
    cd UDPMulticastTest
    make

编译成功的话，会在当前目录下生成两个可执行文件`mcastserver`和`mcastclient`。首先在终端中运行客户端程序`mcastclient`：
    
    ./mcastclient groupAddr port localIfAddr

其中：
- `groupAddr`：组播组地址
- `prot`：端口号
- `localIfAddr`：接收组播数据时采用的网卡地址

然后在另外启动一个终端，运行服务端程序`mcastserver`，服务端程序可以与客户端运行在同一台机器上，也可以运行在不同机器上，但是要保证两台机器之间可以相互通信：

    ./mcastserver groupAddr port localIfAddr

其中：
- `groupAddr`：组播组地址
- `prot`：端口号
- `localIfAddr`：发送组播数据时采用的网卡地址

## 可能存在的问题




