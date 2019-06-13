#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/uio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include "md5.h"
using std::cout; using std::endl;

int main()
{


        int fd1[2];
        int fd2[2];

        char buffer[20];
        char buffer32[10];
        int id;
        if (pipe(fd1)==-1)
        {
            fprintf(stderr, "Pipe Failed" );
            return 1;
        }
        
        if (pipe(fd2)==-1)
        {
                fprintf(stderr, "Pipe Failed" );
                return 1;
        }

        id = fork();
        
        if (id < 0)
        {
                fprintf(stderr, "fork Failed" );
                return 1;
        }

        
        else if (id > 0)
        {
                close(fd1[0]); 
                printf("plain text: ");
                scanf("%20s", buffer);
               
                write(fd1[1], buffer, 20);
                close(fd1[1]);
                wait(NULL);
                close(fd2[1]); 
                read(fd2[0], buffer32, 32);
                close(fd2[0]);

                if(strlen(buffer32)==32) {
                  printf("encrypted by process %d : %s\n",getpid(),buffer32);
                        kill(id, SIGKILL);
                }else{
                        exit(0);
                }
        }
        else
        {
                close(fd1[1]); 
                read(fd1[0], buffer, 20);
                std::string str= md5(buffer);
                close(fd1[0]);
                close(fd2[0]);
                write(fd2[1], str.c_str(), 32);
                close(fd2[1]);
                exit(0);
        }
        return 0;
}