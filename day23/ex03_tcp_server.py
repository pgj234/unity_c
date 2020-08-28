#%%
import socket

#tcp 서버 객체
server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

server_socket.bind( ("127.0.0.1", 8282) )
server_socket.listen(5)

print('wait connect')

client_socket, addr = server_socket.accept()
print(f'connected {addr}')

print('wait data')

data = client_socket.recv(1024)     #데이터를 얼마나 받을지 1024보다 많을 시 나누어서
print(f'received : {addr} : {data.decode()}')

client_socket.sendall('bye'.encode())
client_socket.close()

# %%
