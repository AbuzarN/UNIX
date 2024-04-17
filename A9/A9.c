#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/syscall.h>
#include "common_threads.h"
void *tree(void *arg);
int gettid();
int main(int argc, char *argv[]) 
{
 int ht;
 if (argc != 2) {
 fprintf(stderr, "usage: htree height \n");
 exit(1);
 }
 ht = atoi(argv[1]);
 pthread_t p1;
 Pthread_create(&p1, NULL, tree, &ht);
 Pthread_join(p1, NULL);
 return 0;
}
// It is easier to write a recursive function than an iterative one.
// Remember arg is an address in the stack of the caller.
// I wouldnt modify the value at that location.
void* tree(void* arg) 
{
 int h = *((int*)arg);
 //printf("%d\n",h);
 if (h >= 0){
 pthread_t left, right;
 int left_h = h-1;
 int right_h = h-1;
 
 Pthread_create(&left, NULL, tree, &left_h);
 Pthread_create(&right, NULL, tree, &right_h);
 
 if (h == 0){
 printf("Leaf "); 
 }
 else{
 printf("Int. ");
 }
 printf("Thread ID: %d, Height: %d\n", gettid(), h );
 Pthread_join(left, NULL);
 Pthread_join(right, NULL);
 sleep(.5); 
 }
 
 return NULL;
}
int gettid()
{
 return (syscall(SYS_gettid));
}
