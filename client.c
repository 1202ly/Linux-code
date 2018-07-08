#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdlib.h>

int main(int argc,char *argv[])
{
	if(argc != 3){
		perror("[Usage]: ./client [ip] [port]\n");
		return 1;
	}
	//1
	int fd = socket(AF_INET,SOCK_STREAM,0);
	if(fd < 0){
		perror("socket error\n");
		return 1;
	}
	//2
	struct sockaddr_in server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_port  = htons(atoi(argv[2]));
	server_addr.sin_addr.s_addr = inet_addr(argv[1]);
	int ret = connect(fd,(struct sockaddr*)&server_addr,sizeof(server_addr));
	if(ret < 0){
		printf("connect error\n");
		return 2;
	}
	//3
	while(1){
		char buf[1024] = {0};
		ssize_t read_size = read(0,buf,sizeof(buf)-1);
		if(read_size == 0){
			perror("read error\n");
			return 3;
		}
		buf[read_size] = '\0';
		write(fd,buf,strlen(buf));
		char buf_resp[1024] = {0};
		read_size = read(fd,buf_resp,sizeof(buf_resp)-1);
		if(read_size < 0){
			perror("read error\n");
			return 4;
		}else if(read_size == 0){
			printf("Server closse socket\n");
			return 0;
		}else{
			buf_resp[read_size] = '\0';
		}
		printf("Server response:%s\n",buf_resp);
	}
	return 0;
}
