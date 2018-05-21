#include<stdio.h>
#include<unistd.h>
#include<string.h>
int main()
{
	int fd[2];
	int ret = pipe(fd);
	if(ret<0){
		perror("error pipe");
		return 1;
	}
    int count=0;
	pid_t id=fork();
	if(id==0){//child  ->w
		close(fd[0]);
		const char * msg = "hello father,I am child\n";
		while(10){
			//sleep(1);
			write(fd[1],msg,strlen(msg));
			printf("%d\n",count++);
			sleep(1);
			}
	}else{//father  ->r
	    close(fd[1]);
		char buf[120];
		while(1){
			ssize_t s =read(fd[0],buf,sizeof(buf)-1);
			if(s>0){
				buf[s]='\0';
				printf("father say:%s\n",buf);
				sleep(3);
				break;
			}
			
		}
		close(fd[0]);
		int status=0;
		wait(&status);
		printf("sig:%d\n",status&0x7F);
	}
}
