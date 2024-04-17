#include <stdio.h> // for sscanf, fprintf, perror
#include <stdint.h> // for int32_t
#include <assert.h> // for assert
#include "sr.h"
#include <string.h>
#include <unistd.h>
// include files are not complete. 
// include the appropriate files related to read/write/lseek
// check man pages
// Get the values of all the fields of student record sr from stdin
// Put the record in the appropriate offset of the file described by fd
void
put(int32_t fd)
{
 sr s;
 printf("Enter the student name: "); 
 
 // WRITE THE CODE to read the name from stdin
 fgets(s.name,40,stdin);
 s.name[strlen(s.name)-1] = '\0';
 //printf("%s\n", s.name);
 
 // store it in s.name
 // use fgets()
 // fgets doesnt remove newline. replace '\n' with '\0' in s.name. strlen() will be useful
 
 printf("Enter the student id: ");
 //
 // WRITE THE CODE to read student id from stdin
 scanf("%d",& (s.id) ); 
 
 // store it in s.id
 
 printf("Enter the record index: ");
 //
 // WRITE THE CODE to read record index from stdin
 scanf("%d", & (s.index));
 // store it in s.index
 // WRITE THE CODE to seek to the appropriate offset in fd (lseek(), sizeof() will be useful)
 lseek(fd, sizeof(sr) * s.index, SEEK_SET);
 // WRITE THE CODE to write record s to fd
 write(fd, &s.name, sizeof(s.name));
 write(fd, &s.id, sizeof(s.id));
 write(fd, &s.index, sizeof(s.index));
}
// read the student record stored at position index in fd
void
get(int32_t fd)
{
 sr s;
 int32_t index;
 printf("Enter the record index: ");
 //
 // WRITE THE CODE to get record index from stdin and store in it index
 scanf("%d", &index);
 off_t OffSet = lseek(fd, index * sizeof(s), SEEK_SET);
 // WRITE THE CODE to seek to the appropriate offset in fd
 // The record index may be out of bounds. If so, 
 // print appropriate message and return
 // Check SEEK_DATA on the man page for lseek 
 size_t readPoint = read(fd, &s, sizeof(s)); 
 if (OffSet == -1)
 {printf("error no file");return;}
 else if (readPoint == 0)
 {printf("Out Of bounds\n");return;}
 
 if (index != s.index)
 {printf("No Data at given index \n");return;}
 // WRITE THE CODE to read record s from fd
 // If the record has not been put already, print appropriate message
 // and return
 printf("Student name %s \n", s.name); 
 printf("Student id: %d \n", s.id);
 printf("Record index: %d \n", s.index);
 assert(index == s.index);
}
