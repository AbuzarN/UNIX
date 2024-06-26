
#include <stdio.h> 
#include <stdlib.h> 
#include <stdint.h> 
#include <inttypes.h> 
#include <errno.h> // for EINTR
#include <fcntl.h> 
#include <unistd.h> 
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
// Print out the usage of the program and exit.
void Usage(char*);
// Block size in bytes
#define BSIZE 4096
int 
main(int argc, char** argv) 
{
 int32_t fd;
 // input checking 
 if (argc != 3)
 Usage(argv[0]);
 // open input file
 fd = open(argv[1], O_RDWR);
 if (fd == -1) {
 perror("open failed");
 exit(EXIT_FAILURE);
 }
 // use fstat to get file size
 struct stat fileSize;
 fstat (fd, &fileSize);
 
 // call mmap to map the file to memory. See man page for mmap
 // suggested usage: mmap(NULL, file_size, PROT_READ, MAP_PRIVATE, fd, 0)
 // assign the return value of mmap to pointer variable arr 
 // arr[i] is the ith byte of the file
 // Assume the file to consists of sequence of unsigned 8 bit integer (uint8_t)
 
 uint8_t* vals = mmap(NULL, fileSize.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
 int num = atoi(argv[2]);
 int start = num * BSIZE;
 int end = (num + 1) * BSIZE;
 int small = vals[start];
 int i;
 for (i = start + 1; i < end; ++i) {
 if (vals[i] < small) {
 small = vals[i];
 }
 }
 // The file is logically divided into several blocks. 
 // The size of each block is BSIZE (defined above)
 // find the smallest element in the block # specified by argv[2]
 // print the result
 printf("Smallest byte in block %d is: %d\n", num, small);
 close(fd);
 return EXIT_SUCCESS;
}
void 
Usage(char* s) 
{
 fprintf(stderr, "Usage: %s filename block_num \n", s);
 exit(EXIT_FAILURE);
}
