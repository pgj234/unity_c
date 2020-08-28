#include <iostream>

#include <WinSock2.h>
#include <WS2tcpip.h>

struct S_PACKET {
    unsigned char header;
    unsigned char code;
    float data1;
    float data2;
};

struct S_PACKET_RES {
    float data;
};

#pragma warning(disable:4996)
#pragma comment(lib,"ws2_32.lib") //Winsock Library

int main()
{
    sockaddr_in si_other;
    SOCKET hSocket;
    WSADATA wsa;

    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
    {
        printf("start up error \n");
        return 1;
    }

    hSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (hSocket == SOCKET_ERROR)
    {
        printf("socket create error\n");
        return 1;
    }
    printf("scoket create ok\n");

    //주소 초기화 
    memset(&si_other, 0, sizeof(si_other));
    InetPton(AF_INET, L"127.0.0.1", &si_other.sin_addr.s_addr);
    si_other.sin_family = AF_INET;
    si_other.sin_port = htons(8284);

    printf("send data \n");
    S_PACKET req_packet;
    req_packet.header = 0x01;
    req_packet.code = 0x01;
    req_packet.data1 = 10;
    req_packet.data2 = 3;
    //const char* message = "";

    sendto(hSocket, (const char *)&req_packet, sizeof(S_PACKET), 0, (sockaddr*)&si_other, sizeof(si_other));

    S_PACKET_RES res_packet;
    int recv_len;
    int packet_size = sizeof(si_other);
    recv_len= recvfrom(hSocket, (char *)&res_packet, sizeof(S_PACKET_RES), 0, (sockaddr*)&si_other, &packet_size);

    char _ip[256];
    inet_ntop(AF_INET, &si_other.sin_addr, _ip, sizeof(_ip));

    printf("from : %s : %d\n", _ip, ntohs(si_other.sin_port));
    printf("%f",res_packet.data);

    //printf("press any key\m");
    //getchar();
    //printf("close socket\m");

    closesocket(hSocket);
    WSACleanup();

    return 0;
}