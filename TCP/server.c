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
		//a从客户端读取数据
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
		//b根据请求计算响应
		printf("[client %d] %s\n",new_sock,buf);
		//c把响应结果写回到客户端
		write(new_sock,buf,strlen(buf));
	}
}
int main(int argc,char *argv[])
{
	if(argc != 3){
		perror("Usage: ./server [ip] [port]\n");
		return 1;
	}
	//创建套接字
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
	//3 listen 使用listern允许服务器被客户端连接
	if(listen(listen_sock,5) < 0){  //这里的5表示在操作系统中最多能够保持连接的个数
		perror("listen error\n");
		return 4;
	}
	//4服务器初始化完成，进入事件循环 
	printf("Server Init Ok \n");
	while(1){
		struct sockaddr_in peer;
		socklen_t len = sizeof(peer);
		int new_sock = accept(listen_sock,(struct sockaddr*)&peer,&len);//accept将内核中准备好的连接拿到用户空间中执行
		if(new_sock < 0){
			perror("accept error\n");
			continue;
		}
		Process(new_sock);//连接处理
	}
	return 0;
}
