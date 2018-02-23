#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <wait.h>
#include <errno.h>
int main (int argc ,char *argv[]) {

	char *nom = "file.fifo";
	char ch[BUFSIZ] = "Bonjour";
	int pid;

	if(mkfifo(nom , 0755) != 0) {
		perror("mkfifo");
		exit(1);
	}

	if((pid = fork()) < 0) {
		perror("fork");
		exit(1);
	}

	if(pid == 0) {
		int fd = open(nom , O_RDONLY);
		read(fd , ch , BUFSIZ);
		exit(1);
	}else {
		int fd = open(nom , O_WRONLY);
		write(fd , ch , strlen(ch));
		printf("%s\n", ch);
		wait(NULL);
	}
 
   return 0;
}
