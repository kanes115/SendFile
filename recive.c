#include <stdio.h>
#include <string.h>
#include "connect.h"
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <linux/limits.h>

#define SIZE 512

int reciveFile(int sockfd);
char* getName(char* name);
int getNameExtPos(char* name);

int main(int argc, char* argv[])
{
	if(argc != 2){
		printf("Usage: %s PORT\n", argv[0]);
		return 1;
	}
	int sockfd = startServer(atoi(argv[1]));
	reciveFile(sockfd);

	return 0;
}

int reciveFile(int sockfd)
{
	char* name = (char*)calloc(sizeof(char), PATH_MAX);
	if(recv(sockfd, name, sizeof(char)*PATH_MAX, MSG_WAITALL) < 0){
		perror("Error: recive name");
		return 1;
	}
	char* vname = getName(name);
	FILE* fd = fopen(vname, "w");
	if(!fd){
		perror("Error: fopen");
		return 2;
	}

	char* buff = (char*)calloc(sizeof(char), SIZE);
	if(!buff){
		perror("Error: Failed to allocate memory");
		return 3;
	}
	int read;
	while((read = recv(sockfd, buff, SIZE, 0)) > 0){
		fwrite(buff, sizeof(char), read, fd);
	}
	fclose(fd);
	free(vname);
	free(buff);
	free(name);
	return 1;
}

char* getName(char* name)
{
	char* buff = (char*)calloc(sizeof(char), PATH_MAX+1);
	char* nm = (char*)calloc(sizeof(char), PATH_MAX);
	char* ext = (char*)calloc(sizeof(char), PATH_MAX);
	int pos = getNameExtPos(name);
	strncpy(nm, name, pos);
	strcpy(ext, name+pos);
	strcpy(buff, name);
	int i=1;
	//Add number before extension
	while(access(buff, F_OK) != -1){
		sprintf(buff, "%s%d%s", nm, i, ext);
		i++;
	}
	free(nm);
	free(ext);
	return buff;
}

//return extension position in name
int getNameExtPos(char* name)
{
	int pos = 0;
	char c = *name;
	int i=1;
	for(; c!='\0'; i++){
		c=name[i];
		if(c == '.'){
			pos=i;
		}
	}
	if(pos==0)
		return i-1;
	return pos;
}

