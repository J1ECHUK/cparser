#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <WinSock2.h>

#difine BUFFER_SIZE 1024

#include "dict_of_words.h"
#include "dict_of_tags.h"
#include "search_word.h"
#include "search_tag.h"
#include "search_word_tags.h"
#include "search_link.h"

int main() {

    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        fprintf(stderr, "WSAStartup failed\n");
        return 1;
    }

    const char* url = "en.wikipedia.org";
    SOCKET sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == INVALID_SOCKET) {
        fprintf(stderr, "Error creating socket\n");
        return 1;
    }

    struct hostent* server = gethostbyname(url);
    if (server == NULL) {
        fprintf(stderr, "Error getting host by name\n");
        return 1;
    }

    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(80);
    memcpy(&serverAddr.sin_addr.s_addr, server->h_addr, server->h_length);

    if (connect(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        fprintf(stderr, "Error connecting to server\n");
        return 1;
    }

    char request[256];
    sprintf(request, "GET /wiki/Open-source_intelligence HTTP/1.1\r\nHost: %s\r\nConnection: close\r\n\r\n", url);
    send(sockfd, request, strlen(request), 0);

    char response[BUFFER_SIZE];
    FILE* file = fopen("output.txt", "w");
    if (file == NULL) {
        fprintf(stderr, "Error opening file\n");
        return 1;
    }

    int bytesRead;
    while ((bytesRead = recv(sockfd, response, BUFFER_SIZE, 0)) > 0) {
        fwrite(response, 1, bytesRead, file);
    }

    fclose(file);
    closesocket(sockfd);
    WSACleanup();

    char* filename = "output.txt";
    char* search_words = "open-source intelligence";
    char* search_tags = "h1 h2 p a";
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Error while opening file\n");
        return 0;
    }
    Tags *tags = fill_tags(file);
    fclose(file);

    //print_tags(tags);

    //char *text_for_search_word = str_text_for_search_word(tags, search_words);
    //char *text_for_search_tags = str_text_for_search_tags(tags, search_tags);
    //char *text_for_search_word_tags = str_text_for_search_word_tag(tags, search_tags, search_words);
    //printf("Text for searched word: %s\n\n", text_for_search_word);
    //printf("Text for searched tags: %s\n\n", text_for_search_tags);
    //printf("Text for searched word: %s\n\n", text_for_search_word_tags);

    printf("Text for searched word: %s\n\n", str_text_for_search_link(tags));

    return 0;
}
