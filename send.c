#include <stdio.h>
#include "connect.h"
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <linux/limits.h>

#define SIZE 512

int sendFile(int sockfd, char* name);
int sendName(int sockfd, char* name);

int main(int argc, char* argv[])
{
	if(argc != 4){
		printf("Usage: %s IP PORT FILENAME\n", argv[0]);
		return 1;
	}
	int sockfd = startClient(atoi(argv[2]), argv[1]);
	sendFile(sockfd, argv[3]);

	return 0;
}

int sendFile(int sockfd, char* name)
{
	FILE* fd = fopen(name, "r");
	if(!fd){
		perror("Error: fopen");
		return 2;
	}

	char* buff = (char*)calloc(sizeof(char), SIZE);
	if(!buff){
		printf("Error: Failed to allocate memory");
		return 3;
	}
	
	int read = 0;
	//send filename then file
	if(sendName(sockfd, name) < 0){
		perror("Error: sendName");
		return -1;
	}
	while((read = fread(buff, sizeof(char), SIZE, fd)) > 0){
		if(send(sockfd, buff, read, 0) != read){
			perror("Error: send");
			return 4;
		}
	}
	free(buff);
	if(feof(fd)){
		printf("File sent");
	}
	if(ferror(fd)){
		perror("Error: read");
		fclose(fd);
		return -1;
	}
	fclose(fd);
	return 1;
}

int sendName(int sockfd, char* name)
{
	char* sname = (char*)calloc(sizeof(char), PATH_MAX);
	strcpy(sname, name);
	int res = send(sockfd, sname, PATH_MAX*sizeof(char), 0);
	free(sname);
	return res;
}
