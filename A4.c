
// TASK 1: Include the appropriate files.
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
int main(int argc, char** argv) 
{
 int32_t x = 3377;
 // TASK 2: 
 // Understand the assignment statements below.
 // Do not modify them.
 // Appropriately define the variables p, a, m, z, t 
 int *p = &x; // p now contains the addr of x
 int **a = &p; // a now contains the addr of p
 int ***m = &a; // m now contains the addr of a
 int ****z = &m; // z now contains the addr of m
 int *****t = &z; // t now contains the addr of z
 // TASK 3: 
 // Your next task is to print the value of x by
 // recursively deferencing the above variables.
 // Complete the printf statments below.
 // The variable used should be as per the description
 // of the printf
 printf("x by recursive deref. of p: %d \n", *p);
 printf("x by recursive deref. of t: %d \n", *****t);
 printf("x by recursive deref. of m: %d \n", ***m);
 printf("x by recursive deref. of z: %d \n", ****z);
 printf("x by recursive deref. of a: %d \n", **a);
 char* c;
 // TASK 4: 
 // Find the sizes of c and p
 // Complete the statements below. Hint: sizeof()
 printf("size of c %d \n", sizeof(c));
 printf("size of p %d \n", sizeof(p));
 // TASK 5: 
 // What do you observe? c and p are pointers to two
 // different types. Are their sizes different?
 // Write a brief note justifying your observation
 // at the bottom of the file. 
 // Make sure it is commented.
 
 return EXIT_SUCCESS;
}
/* your observation below
 * The size of both of these pointers are the same (8 bytes) even when they point to two different data types. I believe they are this size 
since the UTD linux environment is 64 bit which has 8 bit pointers.
