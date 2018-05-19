#include <stdio.h>
#include <string.h>
#include "connect.h"
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <linux/limits.h>

#define SIZE 512

int reciveFile(int sockfd, char* name);
char* getName(char* name);

int main(int argc, char* argv[])
{
	if(argc != 2){
		printf("Usage: %s PORT\n", argv[0]);
		return 1;
	}
	int sockfd = startServer(atoi(argv[1]));
	sleep(2);
	reciveFile(sockfd, "CISKOPAKIET");

	return 0;
}

int reciveFile(int sockfd, char* name)
{
	char* vname = getName(name);
	FILE* fd = fopen(vname, "w");
	if(!fd){
		perror("Error: fopen");
		return 2;
	}

	char* buff = (char*)calloc(sizeof(char), SIZE);
	if(!buff){
		printf("Error: Failed to allocate memory");
		return 3;
	}
	int read;
	while((read = recv(sockfd, buff, SIZE, 0)) > 0){
		fwrite(buff, sizeof(char), read, fd);
	}
	fclose(fd);
	free(vname);
	free(buff);
	return 1;
}

char* getName(char* name)
{
	char* buff = (char*)calloc(sizeof(char*), PATH_MAX+1);
	strcpy(buff, name);
	int i=1;
	while(access(buff, F_OK) != -1){
		sprintf(buff, "%s%d", name, i);
		i++;
	}
	return buff;
}

