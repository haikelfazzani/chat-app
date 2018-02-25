#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <wait.h>
#include <stdlib.h>

int main (int argc, char *argv[]){
		
	int fd = open("text.txt" , O_WRONLY);
	dup2(fd , 1);
	execlp("ls","ls",NULL);
	  
    return 0;
}
