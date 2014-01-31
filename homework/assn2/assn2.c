#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int childParent(){
	pid_t child_pid, wpid;
	int status;
	child_pid = fork();
	if(child_pid !=0){
	  printf("PARENT Started. Now waiting for process %d\n", child_pid);
	  if((wpid = wait(&status)) == -1)
	    perror("wait error");
	  printf("PARENT resumed. Child exit code of %d. Now terminating parent\n", 0);
	}else{
	  printf("CHILD Started. No arguments provided. Terminating child\n");
	}
	return 0;
}

int spawnOne(char* program){
	pid_t pid, wpid;
	pid = fork();
	int status;
	if (pid !=0){
	  printf("PARENT started. now waiting on process %d\n", pid);
	  if((wpid=wait(&status))==-1)
	    perror("wait error");
	  printf("PARENT resumed. Child exit code of 0. Now terminating parent\n");
	  return pid;
	}else{
	  printf("CHILD started. One argument provided. Calling execlp(), never to return (sniff)\n");
	  execlp(program, program, NULL);
	  printf("Return not expected. Must be an execlp error.n");
	  _exit(EXIT_FAILURE);
	}
}

int spawn (char* program, char** arg_list){
	pid_t child_pid, wpid;
	int status;
	/*duplicate this process*/
	child_pid = fork();
	if (child_pid != 0){
	  printf("PARENT started. Now waiting for process %d\n", child_pid);
	  if((wpid=waitpid(child_pid,&status, 0))==-1)
	    perror("wait error");
	  printf("PARENT resumed. Child exit code of %d. Now terminating parent\n", status);
	  return child_pid;
	}else{
	  printf("CHILD started. More than one argument provided. calling execvp(), never to return (sniff)\n");
	  execvp(program, arg_list);
	  printf("an error occurred in execvp\n");
	  _exit(EXIT_FAILURE);
	}
}

int main (int argc, char *argv[]){
	char* arg_list[10] = {};
	/*no argmuments*/
	if(argc <= 1){
	  childParent();
   	  return 0;
	}else if(argc == 2){/*one argument*/
	  spawnOne(argv[1]);
	}else{/*multiple arguments*/
	  int i = 0;
	  while(i<argc){
	    if(i+1==argc){
	      arg_list[i] = NULL;
	    }
	    else{
	      arg_list[i] = argv[i+1];
	    }
	    i++;
	  }
	  spawn (argv[1], arg_list);
	}
	printf("done with main program\n");
	return 0;
}
