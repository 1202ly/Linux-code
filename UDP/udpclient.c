#include<stdio.h>
#include<sys/types.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
int main(int argc,char* argv[])
{
	if(argc != 3){
		printf("Usage:./client [ip] [port]\n");
		return 1;
	}
	int sock = socket(AF_INET,SOCK_DGRAM,0);//UDP
    if(sock < 0){
		perror("socket error\n");
		return 2;
	}
	struct sockaddr_in server;
	server.sin_family = AF_INET;//tcp/ip
	server.sin_port = htons(atoi(argv[2]));
    server.sin_addr.s_addr = inet_addr(argv[1]);
	char buf[1024];
	struct sockaddr_in peer;
	while(1){
		socklen_t len = sizeof(peer);
		printf("please enter: ");
		fflush(stdout);
		ssize_t s = read(0,buf,sizeof(buf)-1);
		if(s < 0){
			printf("read error\n");
			return 1;
		}else if(s == 0){
			printf("read done\n");
			return 0;
		}else{
			buf[s-1]=0;
			sendto(sock,buf,strlen(buf),0,\
			(struct sockaddr*)&server,sizeof(server));
			ssize_t ss = recvfrom(sock,buf,sizeof(buf)-1,0,\
			(struct sockaddr*)&peer,&len);
			if(ss < 0){
				printf("recvfrom error\n");
				return 1;
			}
			buf[ss] = 0;
			printf("server say:%s\n",buf);
		}
	}
    return 0;
}
