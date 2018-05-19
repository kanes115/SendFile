#include "connect.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

int startServer(int port)
{
	int listenfd, sockfd;
	struct sockaddr_in myaddr, clientaddr;
	
	if((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		perror("Error: creating listen socket");
		exit(1);
	}
	memset(&myaddr, 0, sizeof(myaddr));
	myaddr.sin_addr.s_addr = INADDR_ANY;
	myaddr.sin_port = htons(port);
	myaddr.sin_family = AF_INET;

	if(bind(listenfd, (struct sockaddr*)&myaddr, sizeof(struct sockaddr)) < 0){
		perror("Error: binding listen socket");
		exit(1);
	}
	if(listen(listenfd, NCON) < 0){
		perror("Error: listening");
		exit(1);
	}
	
	int claddrsize = sizeof(clientaddr);
	if((sockfd = accept(listenfd, (struct sockaddr*)&clientaddr, &claddrsize)) < 0){
		perror("Error: accept");
		exit(1);
	}
	return sockfd;
}

int startClient(int port, char* ip)
{
	int sockfd;
	struct sockaddr_in servaddr;

	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		perror("Error: creating socket");
		exit(1);
	}
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_port = htons(port);
	servaddr.sin_family = AF_INET;
	if((inet_pton(AF_INET, ip, &servaddr.sin_addr)) < 0){
		perror("Error: pton");
		exit(1);
	}

	if(connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0){
		perror("Error: connect");
		exit(1);
	}
	return sockfd;
}


