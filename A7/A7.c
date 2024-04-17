#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
 * This program counts the number of sentences in a given string and
 * the number of tokens in each sentence.
 * Terminates when user enters BYE
 */
int countWords(char *input) 
{
 int count = 0;
 char *saveptr;
 char *token = strtok_r(input, " ", &saveptr);
 while (token != NULL) {
 count++;
 token = strtok_r(NULL, " ", &saveptr);
 }
 return count;
}
int main(int argc, char *argv[])
{
 // define the required variables
 char bye[4] = "BYE\n";
 char *input = NULL;
 size_t len = 0;
 ssize_t read;
 while (1) 
 {input = NULL;
 printf("Enter the string: ");
 if ((read = getline(&input, &len, stdin)) != -1) {
 char *token = strtok(input, "."); 
 int itter =1;
 while (token != NULL) 
 {
 while (isspace(*token)) 
 {
 token++;
 }
 char *temp = token;
 int wc = countWords(temp);
if (strcmp(bye, temp) == 0)
 {
 exit(EXIT_SUCCESS);
 }
 else if (wc > 0)
 {
 printf("Sentence %d: tokens ", itter);
 printf("%d.\n", wc);
 }
 token = strtok(NULL, ".");
 itter++;
 }
 }
 // use getline() to get the input string
 // The input string consists of several sentences separated by '.'
 // Each sentence consists of several tokens separated by ' ' (space).
 // Using strtok_r() find the number of sentences and the number of tokens
 // in each sentence. HINT: man strtok and look at the sample program at the end.
 // Print the results.
 // If the first token is BYE, break from the while loop (check strcmp/strncmp)
 free(input);
 }
 exit(EXIT_SUCCESS);
}
