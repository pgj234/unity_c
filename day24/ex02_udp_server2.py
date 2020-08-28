#%%
import socket
from struct import *

udp_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

udp_socket.bind(('', 8284))

print('init socket')

#%%
while True :
    print('wait request...')
    _data, _rinfo = udp_socket.recvfrom(1024)
    print(_data)
    print(_rinfo)
    _packet = unpack("BBff", _data)

    if _packet[0] == 0x01 :     # 요청 코드 1 처리
        if _packet[1] == 0x01 :     # 덧셈
            _res = pack("f", _packet[2] + _packet[3])
            
            pass
        elif _packet[1] == 0x02 :   # 뺄셈
            _res = pack("f", _packet[2] - _packet[3])

            pass
        elif _packet[1] == 0x03 :   # 곱셈
            _res = pack("f", _packet[2] * _packet[3])

            pass
        elif _packet[1] == 0x04 :   # 나눗셈
            _res = pack("f", _packet[2] / _packet[3])

            pass
    else :
        _res = pack("Bh", 0xff, 0)

    udp_socket.sendto(_res, (_rinfo[0], _rinfo[1]))
    print('response ok')