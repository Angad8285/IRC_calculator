#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

void error(char *msg) {
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        error("Specify port");
    }

    int sockfd, newsockfd, portno, n, bl = 10;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len;
    char buffer[bl];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        error("error creating socket for server.");
    }

    bzero((struct sockaddr *) &server_addr, sizeof(server_addr));
    portno = atoi(argv[1]);

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(portno);

    if (bind(sockfd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) error("binding error");

    listen(sockfd, 1);

    client_len = sizeof(client_addr);
    newsockfd = accept(sockfd, (struct sockaddr *) &client_addr, &client_len);

    if (newsockfd < 1) error("error accepting message");

    // while(1) {
    //     bzero(buffer, bl);
    //     fgets(buffer, bl, stdin);
    //     n = write(newsockfd, buffer, strlen(buffer));
    //     if (n < 0) printf("error writing message");
        
    //     // int i = strncmp("z", buf)
        

    //     bzero(buffer, bl);
    //     n = read(newsockfd, buffer, bl);
    //     if (n < 0) error("error reading message");
    //     printf("server: %s\n", buffer);

    //     if (strncmp("z", buffer, 1) == 0) break;
    // }

    int num1, num2, answer, choice;

S : n = write(newsockfd, "enter first number: ", sizeof("enter first number: "));
    if (n < 0) error("error writing to socket");
    read(newsockfd, &num1, sizeof(int));
    printf("client's first number is: %d\n", num1);

    n = write(newsockfd, "enter second number: ", sizeof("enter second number: "));
    if (n < 0) error("error writing to socket");
    read(newsockfd, &num2, sizeof(int));
    printf("client's second number is: %d\n", num2);

    n = write(newsockfd, "1 add, 2 sub, 3 multiply, 4 division, 5 exit", sizeof("1 add, 2 sub, 3 multiply, 4 division, 5 exit"));
    if (n < 0) error("error writing to socket");
    read(newsockfd, &choice, sizeof(int));
    printf("the operation you chose is: %d\n", choice);

    switch (choice) {
        case 1: 
        answer = num1 + num2;
        break;
        case 2:
        answer = num1 - num2;
        break;
        case 3: 
        answer = num1 * num2;
        break;
        case 4: 
        answer = num1 / num2;
        break;
        case5:
        goto Q;
        break;
    }

    write(newsockfd, &answer, sizeof(int));
    if (choice != 5)
        goto S;

Q : close(newsockfd);
    close(sockfd);
    return 0;
}