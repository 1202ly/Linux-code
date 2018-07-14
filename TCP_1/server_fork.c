#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<signal.h>
//./server [ip] [port]
void Process(int new_sock,struct sockaddr_in peer){
	int ret = fork();
	if(ret < 0){
		perror("fork error\n");
		return;
	}
	if(ret > 0){
		//father
		close(new_sock);
		return;
	}
	//child
	 while(1){
		//a
     	char buf[1024] = {0};
		ssize_t read_size = read(new_sock,buf,sizeof(buf)-1);
		if(read_size < 0 ){
			continue;
		}
		if(read_size == 0){
			printf("[client %s:%d] disconnect!\n",\
			inet_ntoa(peer.sin_addr),ntohs(peer.sin_port));
			close(new_sock);
			exit(0);
		}
		buf[read_size] = '\0';
		//b
			printf("[client %s:%d] %s\n",\
			inet_ntoa(peer.sin_addr),ntohs(peer.sin_port),buf);
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
	signal(SIGCHLD,SIG_IGN);
	int listen_sock = socket(AF_INET,SOCK_STREAM,0);
	if(listen_sock < 0){
		perror("socket error\n");
		return 2;
	}
	//2 绑定端口号
	struct sockaddr_in client_addr;
	client_addr.sin_family = AF_INET;
	client_addr.sin_port = htons(atoi(argv[2]));
	client_addr.sin_addr.s_addr = inet_addr(argv[1]);
	if(bind(listen_sock,(struct sockaddr*)&client_addr,sizeof(client_addr))<0){
		perror("bind error\n");
		return 3;
	}
	//3 监听事件---》使用listen允许服务器被客户端连接
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
		printf("[client %s:%d] connect\n",inet_ntoa(peer.sin_addr),\
		ntohs(peer.sin_port));
		Process(new_sock,peer);
	}
	return 0;
}
