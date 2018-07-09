#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

//./server [ip] [port]
void Process(int new_sock){
	while(1){
		//a
     	char buf[1024] = {0};
		ssize_t read_size = read(new_sock,buf,sizeof(buf)-1);
		if(read_size < 0 ){
			continue;
		}
		if(read_size == 0){
			printf("[client %d] disconnet\n",new_sock);
			close(new_sock);
			return;
		}
		buf[read_size] = '\0';
		//b
		printf("[client %d] %s\n",new_sock,buf);
		//c
		write(new_sock,buf,strlen(buf));
	}
}
int main(int argc,char *argv[])
{
	if(argc != 3){
		perror("Usage: ./server [ip] [port]\n");
		return 1;
	}
	int listen_sock = socket(AF_INET,SOCK_STREAM,0);
	if(listen_sock < 0){
		perror("socket error\n");
		return 2;
	}
	//2 bangding duankouhao
	struct sockaddr_in client_addr;
	client_addr.sin_family = AF_INET;
	client_addr.sin_port = htons(atoi(argv[2]));
	client_addr.sin_addr.s_addr = inet_addr(argv[1]);
	if(bind(listen_sock,(struct sockaddr*)&client_addr,sizeof(client_addr))<0){
		perror("bind error\n");
		return 3;
	}
	//3 listen
	if(listen(listen_sock,5) < 0){
		perror("listen error\n");
		return 4;
	}
	//4
	printf("Server Init Ok \n");
	while(1){
		struct sockaddr_in peer;
		socklen_t len = sizeof(peer);
		int new_sock = accept(listen_sock,(struct sockaddr*)&peer,&len);
		if(new_sock < 0){
			perror("accept error\n");
			continue;
		}
		Process(new_sock);
	}
	return 0;
}
