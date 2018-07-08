.PHONY:all
all:udpserver udpclient
udpserver:udpserver.c 
	gcc -o $@ $^
udpclient:udpclient.c
	gcc -o $@ $^
.PHONY:clean
clean:
	rm -rf udpserver udpclient
