#include <iostream>
#include <winsock2.h>
#include <Ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

int main() {
    WSADATA wsaData;
    SOCKET socketCli;
    char msg[32];

    sockaddr_in addrServer;

    struct sockaddr_in addrServer;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    socketCli = socket(AF_INET, SOCK_STREAM, 0);

    //접속할 서버 주소 구조체 만들기
    addrServer.sin_family = AF_INET;
    addrServer.sin_port = htonl(8282);
    //addrServer.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
    memset((char*)&addrServer, 0, sizeof(addrServer));
    InetPton(AF_INET, L"127.0.0.1", &addrServer.sin_addr.S_un.S_addr);

    printf("connecting server \n");
    //서버에 접속
    if (connect(socketCli, (struct sockaddr*)&addrServer, sizeof(addrServer)) == SOCKET_ERROR) {
        printf("error code : %d \n", WSAGetLastError());
        return 1;
    }

    printf("connected server \n");

    send(socketCli, "hello TCP", 10, 0);

    closesocket(socketCli);

    return 0;
}