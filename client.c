#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>

int main(int argc , char *argv[]) {

	char buffer[BUFSIZ];
	struct sockaddr_in addr;

	int s = socket(AF_INET, SOCK_STREAM,0);

	addr.sin_family = AF_INET;
	addr.sin_port = htons(atoi(argv[1]));
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	connect(s , (struct sockaddr *)&addr ,sizeof(addr));

	//char str[100];
    while(1) {
    	read(0,buffer , BUFSIZ);
    	if(strcmp(buffer , "quit"))
    		break;
    }

	write(s , buffer , strlen(buffer));
	read(s , buffer , sizeof(buffer));
	printf("%s\n", buffer);
	
	close(s);
}
