#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<string.h>
#include<fcntl.h>
int main()
{
	int fd=open("./fifo",O_WRONLY);
	if(fd < 0){
		perror("error open");
		return 2;
	}
	char buf[100];
	while(1){
		buf[0]=0;
		printf("PLease Enter: ");
		scanf("%s",buf);
		if(strcmp(buf,"quit")==0){
			break;
		}
		write(fd,buf,strlen(buf));
	}
	close(fd);
	return 0;
}
