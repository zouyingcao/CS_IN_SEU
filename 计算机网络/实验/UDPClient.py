from socket import *  # 该socket模块形成了在python中所有网络通信的基础，可在程序中创建套接字

serverName = '192.168.1.103'  # 本机IPv4 地址
serverPort = 12000

# 创建客户套接字，第一个参数是地址簇，AF_INET指示了底层网络使用了Ipv4
# 第二个参数指示了该套接字是SOCK_DGRAM类型的，这意味着它是一个UDP套接字，而不是TCP套接字，SOCK_STREAM类型是一个TCP套接字
clientSocket = socket(AF_INET, SOCK_DGRAM)
# 值得注意的是，我们并没有指定客户套接字的端口号；相反，我们让操作系统为我们做这件事

message = input('Input lowercase sentence:')  # 发送的报文

# .encode()将报文由字符串类型转换为字节类型，
# sendto()为报文附上目的地址(serverName, serverPort)并且向进程的套接字clientSocket发送结果分组
clientSocket.sendto(message.encode(), (serverName, serverPort))
# 当然，源地址也附到分组上，但这个是自动完成的，而不是显式地由代码完成的

# recvfrom()也取缓存长度2048作为输入
modifiedMessage, serverAddress = clientSocket.recvfrom(2048)  # serverAddress包含了服务器的IP地址和端口号
# 将报文从字节转化为字符串
print(modifiedMessage.decode())
# 关闭套接字
clientSocket.close()
