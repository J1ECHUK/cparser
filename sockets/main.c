#include <unistd.h>
#include <WinSock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFFER_SIZE 1024

int main() {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("WSAStartup failed\n");
        return 1;
    }

    SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == INVALID_SOCKET) {
        printf("Error creating socket\n");
        return 1;
    }

    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Указывайте IP адрес сервера
    serverAddr.sin_port = htons(5000); // Порт сервера

    if (connect(sock, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        printf("Error connecting to server\n");
        return 1;
    }

    const char *request = "GET / HTTP/1.1\r\nHost: localhost:5000\r\nConnection: close\r\n\r\n";

    if (send(sock, request, strlen(request), 0) == SOCKET_ERROR) {
        printf("Error sending request\n");
        return 1;
    }

    char buffer[4096];
    int bytesReceived;

    FILE *file = fopen("output.txt", "w");
    if (file == NULL) {
        fprintf(stderr, "Error opening file\n");
        return 1;
    }

    while ((bytesReceived = recv(sock, buffer, sizeof(buffer), 0)) > 0) {
        //printf("%.*s", bytesReceived, buffer);
        fwrite(buffer, 1, bytesReceived, file);
    }

    fclose(file);
    closesocket(sock);
    WSACleanup();

    return 0;
}
//
//int main() {
//    WSADATA wsaData;
//    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
//        fprintf(stderr, "WSAStartup failed\n");
//        return 1;
//    }
//
//    const char *url = "http://localhost:5000/";
//    SOCKET sockfd = socket(AF_INET, SOCK_STREAM, 0);
//    if (sockfd == INVALID_SOCKET) {
//        fprintf(stderr, "Error creating socket\n");
//        return 1;
//    }
//
//    struct hostent *server = gethostbyname(url);
//    if (server == NULL) {
//        fprintf(stderr, "Error getting host by name\n");
//        return 1;
//    }
//
//    struct sockaddr_in serverAddr;
//    serverAddr.sin_family = AF_INET;
//    serverAddr.sin_port = htons(80);
//    memcpy(&serverAddr.sin_addr.s_addr, server->h_addr, server->h_length);
//
//    if (connect(sockfd, (struct sockaddr *) &serverAddr, sizeof(serverAddr)) < 0) {
//        fprintf(stderr, "Error connecting to server\n");
//        return 1;
//    }
//
//    char request[256];
//    sprintf(request, "GET / HTTP/1.1\r\nHost: %s\r\nConnection: close\r\n\r\n", url);
//    send(sockfd, request, strlen(request), 0);
//
//    char response[BUFFER_SIZE];
//    FILE *file = fopen("output.txt", "w");
//    if (file == NULL) {
//        fprintf(stderr, "Error opening file\n");
//        return 1;
//    }
//
//    int bytesRead;
//    while ((bytesRead = recv(sockfd, response, BUFFER_SIZE, 0)) > 0) {
//        fwrite(response, 1, bytesRead, file);
//    }
//
//
//
//    fclose(file);
//    closesocket(sockfd);
//    WSACleanup();
//}