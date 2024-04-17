
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#define DEBUG 0
/* 
 * This function creates a duplicate of string src
 * Memory for duplicate is allocated
 * Pointer to the duplicate is stored in *dup
*/
void strdupe(char* src, char** dup)
{
 // define required variables
 int size = 0;
 char *ptr;
 char *temp;
 ptr = src;
 temp = src;
 while (*ptr != '\0')
 {
 size++;
 ptr++;
 }
 *dup = (char*)malloc((size+1) *sizeof(char));
 
 ptr = *dup;
 while (*src)
 {
 *ptr++ = *src++;
 }
 *ptr = '\0';
 src=temp;
// *ptr=0;
 
 // Find the length of source (src) string
 // Do not use any library call such as strlen()
 // Assume source string is terminated with null character ('\0')
 // allocate memory from heap for the duplicate and store the address 
 
 // if memory allocation fails print appropriate error message 
 // and return
 // copy src to *dup. 
 // Do not use any library call such as strcpy()
 // Do not use array indexing. Use pointer arithmetic.
 
#if DEBUG
 printf("str: %s \n", src);
 printf("str: %s \n", *dup);
#endif
 
 return;
}
