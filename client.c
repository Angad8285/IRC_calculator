#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> //used for reading and writing
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> //defines hostent

void error(char *msg) {
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "specify both, port and server ip address");
        exit(1);
    }
    int sockfd, portno, n;
    struct sockaddr_in server_addr;
    struct hostent *server; //used to store information of the host

    char buffer[256]; 

    portno = atoi(argv[2]); //portno we enter when we call the client after we've compiled it is a string 
    //a to i () function converts it into integer data type

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) error("error creating socket for your client");

    server = gethostbyname(argv[1]); //sets the value of server i.e, parameters of the server hostent equal to the ones given by the ip address
    if (server == NULL) {
        fprintf(stderr, "Provide a valid server ip adress");
    }

    bzero((char *) &server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    bcopy((char *) server->h_addr, (char *) &server_addr.sin_addr.s_addr, server->h_length); 
    //this copies the h_addr from the server whose arguments come from the ip address provided to server_addr.sin_addr.s_addr
    server_addr.sin_port = htons(portno);

    if ( connect(sockfd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) {
        error("connection failed");
    }

    int num1, num2, answer, choice;

S : bzero(buffer ,256);
    n = read(sockfd, buffer, 256);
    if (n < 0)
    error ("ERROR reading from socket");
    printf("Server- %s\n" , buffer);
    scanf("%d", &num1);
    write(sockfd, &num1, sizeof(int));

    bzero(buffer ,256);
    n = read(sockfd, buffer, 256);
    if (n < 0)
    error ("ERROR reading from socket");
    printf("Server- %s\n" , buffer);
    scanf("%d", &num2);
    write(sockfd, &num2, sizeof(int));

    bzero(buffer ,256);
    n = read(sockfd, buffer, 256);
    if (n < 0)
    error ("ERROR reading from socket");
    printf("Server- %s\n" , buffer);
    scanf("%d", &choice);
    write(sockfd, &choice, sizeof(int));

    if (choice == 5) goto Q;

    read(sockfd, &answer, sizeof(int));
    printf("Server: The answer is: %d\n", answer);

    if (choice != 5) goto S;

Q : printf("You have chose to exit.");
    close(sockfd);
    return 0;
}