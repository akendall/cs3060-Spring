#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include<pthread.h>

/*Andrew Kendall
cs3060-001 Spring
assn1

I promise that this source code file has, in its entirety, been written by
myself and by no other person. If at any time an exact copy of this source
code is found to be used by another person in this term, I understand that
both myself and the student that submitted the copy will recieve zero on this
project*/

int fib;
pthread_mutex_t counter_lock = PTHREAD_MUTEX_INITIALIZER;

void* fibonacci(void *n)
{
  int a=0,b=1,c,i;
  pthread_mutex_lock(&counter_lock);
  if(atoi(n)==1){
    printf("Fibonacci sequence: ");
    printf("%d\n",a);
    exit(0);
  }
  else if(atoi(n)==2){
    printf("Fibonacci sequence: ");
    printf("%d, %d",a,b);
    exit(0);
  }else{
    printf("Fibonacci sequence: ");
    printf("%d, %d, ",a,b);
    for(i=0;i<atoi(n)-2;i++)
    {
      c=a+b;
      printf("%d, ",c);
      a=b;
      b=c;
    }
    printf("\n");
    pthread_exit(0);
  }
  pthread_mutex_unlock(&counter_lock);
  return NULL; 
}
 
int main(int argc,char* argv[])
{
  pthread_t thread;
 
  if(argc!=2)
  {
    fprintf(stderr,"Syntax: ./a.out <integer value>");
    return -1;
  }
  if(atoi(argv[1])<0)
  {
    fprintf(stderr,"Argument %d must be positive value\n",atoi(argv[1]));
    return -1;
  }
 
  pthread_create(&thread,NULL,fibonacci,(void*)argv[1]);
 
  pthread_join(thread,NULL);
 
  return 0;
}
