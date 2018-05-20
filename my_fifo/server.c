#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<string.h>
#include<fcntl.h>
int main()
{
	if(mkfifo("./fifo",0644)<0){
		perror("error mkfifo\n");
		return 1;
	
	}
	int fd=open("./fifo",O_RDONLY);
	if(fd < 0){
		perror("error open");
		return 2;
	}
	char buf[100];
	while(1){
		ssize_t s= read(fd,buf,sizeof(buf)-1);
		if(s > 0){
			buf[s]='\0';
			printf("client---->server: %s\n",buf);
		}else if(s==0){
			printf("client quit\n");
			break;
		}
	}
	close(fd);
	return 0;
}
