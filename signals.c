// CPP code to create three child 
// process of a parent 
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/uio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <wait.h>
#include <sys/wait.h>
#include <sys/fcntl.h>
int cpid [5];
int j; 
int sigCatcher() {  
  signal(SIGINT, sigCatcher);  
  printf("PID %d caught one\n", getpid());
  if(j > -1)
    	kill(cpid[j], SIGINT);  // send signal to next child in cpid
}
int main() {
  int zombiechild;
  int pid;
signal(SIGINT , sigCatcher);
  int state;

 for(int i=0; i<5; i++){
    if((pid=fork()) ==  0){      		// create new child
      	printf("PID %d ready\n", getpid());
      	j = i-1;
	pause(); 			// wait for signal
     	exit(0);  			
    }
    else            		
      	cpid[i] = pid;	  
} 
sleep(3);     			
kill(cpid[4], SIGINT);     	
sleep(3);                 			 
for(int i=0; i<5; i++){
    zombiechild = wait(&state); 		
    printf("%d is dead\n", zombiechild);
  }
  exit(0);
}
