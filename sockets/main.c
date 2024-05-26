#include <unistd.h>
#include <WinSock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define BUFFER_SIZE 1024

char *load_url(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Error opening file\n");
        return NULL;
    }

    char *url = NULL;
    char c;
    int len = 0;

    while ((c = fgetc(file)) != EOF) {
        url = realloc(url, (len + 1) * sizeof(char));
        url[len] = c;
        len++;
    }

    url = realloc(url, (len + 1) * sizeof(char));
    url[len] = '\0';

    fclose(file);
    return url;
}

char *extractDomainName(char *url) {
    char *domain = NULL;
    char *start = strstr(url, "://");

    if(start != NULL) {
        start += 3;
        char *end = strchr(start, '/');
        if(end != NULL) {
            int length = end - start;
            domain = (char *)malloc((length + 1) * sizeof(char));
            strncpy(domain, start, length);
            domain[length] = '\0';
        }
    }
    return domain;
}

char *extractPathFromUrl(const char *url) {
    char *path;
    const char *ptr = strchr(url + 8, '/');
    if (ptr) {
        strcpy(path, ptr);
    } else {
        strcpy(path, "/");
    }
    return path;
}

int extractPortFromUrl(char* url) {
    char* portPtr = strstr(url, ":");
    if (portPtr != NULL) {
        return atoi(portPtr + 1);
    }
    return 80;
}


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

    struct addrinfo* result = NULL;
    struct addrinfo hints;

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    char *url;
    url = load_url("C:\\Users\\New\\Downloads\\temp\\sockets\\url.txt");
    char *domain = extractDomainName(url);
    char *path = extractPathFromUrl(url);


    if (getaddrinfo("127.0.0.1", "5000", &hints, &result) != 0) {
        fprintf(stderr, "Failed to get IP address for the specified URL\n");
        return 1;
    }

    if (connect(sock, result->ai_addr, (int)result->ai_addrlen) == SOCKET_ERROR) {
        printf("Error connecting to server\n");
        freeaddrinfo(result);
        return 1;
    }

    const char *request = malloc(100);
    sprintf(request, "GET %s HTTP/1.1\r\nHost: %s\r\nConnection: close\r\n\r\n", path,  domain);
    printf("GET %s HTTPS/1.1\r\nHost: %s\r\nConnection: close\r\n\r\n", path,  domain);

    if (send(sock, request, strlen(request), 0) == SOCKET_ERROR) {
        printf("Error sending request\n");
        freeaddrinfo(result);
        return 1;
    }

    char buffer[4096];
    int bytesReceived;

    FILE* file = fopen("C:/Users/New/Downloads/temp/cProject/html.txt", "w");
    if (file == NULL) {
        fprintf(stderr, "Error opening file\n");
        freeaddrinfo(result);
        return 1;
    }

    while ((bytesReceived = recv(sock, buffer, sizeof(buffer), 0)) > 0) {
        //printf("%s", buffer);
        fwrite(buffer, 1, bytesReceived, file);
    }

    fclose(file);
    closesocket(sock);
    freeaddrinfo(result);
    WSACleanup();

    return 0;
}
