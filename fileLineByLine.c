#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <wait.h>
#include <stdlib.h>

int main (int argc, char *argv[]){

        int i = 0 , j = 0;

        char buf[255];

        int fp = open (argv[1], O_RDONLY);
        while (read (fp, buf+(i++), 1) != 0){

                while (buf[i-1] != '\n'){
                        read (fp, &buf[i++], 1);
                }       buf[i] = '\0';
                j++;
                printf("La ligne est : %s", buf);
                //traitement à faire ici;

                buf[0] = '\0';
                i=0;

        }
        printf("%d\n", j);
        return 0;
}
