"""
作者:czy
日期:2021年 10月 06日
"""
from socket import *

serverPort = 12000
serverSocket = socket(AF_INET, SOCK_DGRAM)
# 将端口号12000与该服务器的套接字绑定（即分配）在一起
serverSocket.bind(('', serverPort))
print("The server is ready to receive")

while True:
    message, clientAddress = serverSocket.recvfrom(2048)  # clientAddress包含了客户的IP地址和端口号
    modifiedMessage = message.decode().upper()  # 转换为大写
    serverSocket.sendto(modifiedMessage.encode(), clientAddress)
