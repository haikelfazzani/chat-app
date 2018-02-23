#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>


int main(int argc , char *argv[]) {

	struct sockaddr_in addr;
	struct hostent *htpr;
	char buffer[BUFSIZ];

	int s = socket(AF_INET , SOCK_STREAM , 0);

	addr.sin_family = AF_INET;
	addr.sin_port = htons(atoi(argv[2]));
	htpr = gethostbyname(argv[1]);
	memcpy(&addr.sin_addr, htpr->h_addr , htpr->h_length);

	connect(s , (struct sockaddr *)&addr , sizeof(addr));

	while(1) {
		
		strcpy(buffer , 0);
		write(s , buffer , strlen(buffer));
		fflush(stdin);
		read( s , buffer , BUFSIZ);
		//printf("%s\n", buffer);
	}
	close(s);
}
