"""
作者:czy
日期:2021年 10月 06日
"""
from socket import *

serverName = '192.168.1.103'  # 本机IPv4 地址
serverPort = 12000

clientSocket = socket(AF_INET, SOCK_STREAM)  # SOCK_STREAM类型是一个TCP套接字
clientSocket.connect((serverName, serverPort))  # 创建一个TCP连接

message = input('Input lowercase sentence:')  # 发送的报文
clientSocket.send(message.encode())  # 客户程序只是把字符串message放入TCP连接中

modifiedMessage = clientSocket.recv(2048)
print('From Server:', modifiedMessage.decode())
clientSocket.close()
