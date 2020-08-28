#%%
import socket

udp_socket = socket.socket(socket.AF_INET, socket.socket)

print('init socket')

udp_socket.sendto("hello".encode(), ('127.0.0.1', 8284))

#%%