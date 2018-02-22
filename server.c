#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc ,char *argv[]) {

	char buffer[1024];
	struct sockaddr_in addr;

	int s = socket(AF_INET,SOCK_STREAM,0);

	addr.sin_family = AF_INET;
	addr.sin_port = htons(atoi(argv[1]));
	addr.sin_addr.s_addr = htonl(INADDR_ANY);

	bind(s , (struct sockaddr *)&addr , sizeof(addr));

	listen(s,5);

	while(1) {
		int sinlen = sizeof(addr);
		int ac = accept(s,(struct sockaddr *)&addr ,&sinlen);
		read(ac , buffer , sizeof(buffer));
		write(ac ,buffer , strlen(buffer));
		printf("%s\n", buffer);
		close(ac);
	}
	close(s);
}
