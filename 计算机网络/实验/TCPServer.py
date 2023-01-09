"""
作者:user
日期:2021年 10月 06日
"""
from socket import *

serverPort = 12000
serverSocket = socket(AF_INET, SOCK_STREAM)  # 欢迎套接字
serverSocket.bind(('', serverPort))
serverSocket.listen(1)  # 欢迎之门，等待并聆听某个客户敲门，请求TCP连接的最大数为1
print("The server is ready to receive")

while True:
    connectionSocket, address = serverSocket.accept()  # 连接套接字：新的套接字，由这个特定的客户专用
    sentence = connectionSocket.recv(1024).decode()
    modifiedMessage = sentence.upper()  # 转换为大写
    connectionSocket.send(modifiedMessage.encode())
    connectionSocket.close()
