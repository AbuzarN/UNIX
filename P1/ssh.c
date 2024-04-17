// Imported libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
// Definitions
#define HISTORY_SIZE 100
#define ARGS_LIMIT 100
//History is stored as a global pointer arrays
char *history [HISTORY_SIZE];
//pseudo circular array with a pointer to denote most recent element
int front = 0;
int rear = -1;
int itemCount = 0;
// Function prototypes
void clearHistory();
void displayHistory();
void execute(char **args);
void execute_pipes (char **args, int num);
void insert (char *line);
void tokenizeExecute(char *line, int flag);
//Resetting history and historyPtr to original state (every element in history is NULL)
void clearHistory(){
 for (int i = 0; i<HISTORY_SIZE; i++){
 history[i] = NULL;
 }
 front = 0;
 rear = -1;
 itemCount = 0;
 
}
//Goes through all the spots of the history array starting at the historypointer and using modulo it loops around the entire array once
// Makes sure all entires are visited while looping until itemCount filled items are encountered in history
void displayHistory(){
 int _ = 0;
 for(int i = front; _<itemCount; i = (i + 1) % HISTORY_SIZE){
 if (history [i] != NULL){
 printf("%d", _ );
 printf(" %s\n", history[i]);
 _++;
 }
 }
}
// Execute function used for executing the shell commands with the parsed command (args)
void execute(char **args) {
 
 if (args[0] == NULL){
 
 }else if (strcmp(args[0], "exit") == 0){
 // If the command is exit, then terminate the program successfully
 exit(EXIT_SUCCESS);
 }else if (strcmp(args[0], "cd") == 0){
 if (args[1] == NULL){
 // If there is no other token then print error
printf("cd: missing directory\n");
 }else{
 // Otherwise, try to change directory and check for error
 if (chdir(args[1]) == -1){
 perror("chdir");
 }
 }
 // If the command is history
 }else if (strcmp(args[0], "history") == 0){
 // If there are no other arguments then display entire history
 if (args[1] == NULL){
 insert("history");
 displayHistory();
 }else if ( strcmp(args[1], "-c") == 0){
 // If the -c option is passed, then clear the history
 clearHistory();
 }else{
 // Otherwise, display history with offset
 int num = atoi(args[1]);
 if (num == 0 && *args[1] != '0'){
 printf("Seconds argument incorrect");
 }else{ 
 tokenizeExecute( strdup(history[(front + num) %HISTORY_SIZE]), 1);
 }
 }
 }else{
 // Otherwise, if the command is not cd, exit, or history, then fork the process
 int id = fork();
 if (id == 0){
 // If child process, execute command with execvp
 execvp(args[0], args);
 perror("execvp");
 exit(EXIT_FAILURE);
 }else if (id < 0) {
 // If error 
 perror("fork");
 }else{
 // If parent process, then wait for child process to complete
 wait(NULL);
 }
 
 } 
}
// Function to handle pipes and piping in our shell
void execute_pipes (char **args, int num){
 char **myArgs[ARGS_LIMIT];// Stores parsed tokens
 int a = 0;
 // For every piped command, extract the tokens of the command and store each full command in myArgs
 for (a =0; a<num; a++){
 char *token;
char *temp[ARGS_LIMIT];
int i = 0;
 char *r = strdup(args[a]);
 // Store parsed command tokens in temp
 while((token = strtok_r(r, " ", &r))){
 temp[i] = strdup(token);
 i++;
 }
 temp[i] = NULL;
 
// Allocate space for command in myArgs and store temp into it, this is done to prevent erors in array assignment
 myArgs[a] = malloc((i + 1) * sizeof(char *));
 
for (int j = 0; j <= i; j++) {
 myArgs[a][j] = temp[j];
 
 }
 }
 // Create vars needed for pipe
 int i = 0;
 int fd[2];
 pid_t pid;
 int fd2 = 0;
 // While commands/tokens are not NULL, open pipe, fork process, and direct output accordingly
 while ( myArgs[i ] != NULL) {
 pipe(fd);
 // Fork process
if ((pid = fork()) == -1) {
 perror("fork");
exit(1);
 }else if (pid == 0) {
 // If child process, then direct output to pipe
 dup2(fd2, 0);
 if (myArgs[i + 1] != NULL) {
 dup2(fd[1], 1);
 }
 close (fd[0]);
 execvp(myArgs[i][0], myArgs[i]);
 exit(1);
 }else{
 // If parent process, then close write end and wait for child process to end
 close(fd[1]);
 fd2 = fd[0];
 wait(0);
 
 }
 i++;
 }
}
// Insert function to insert last entered command from user (line parameter), resizing if itemCount == HISTORY_SIZE and updating necessary 
variables
void insert (char *line){
 if (itemCount == HISTORY_SIZE){
 front = (front + 1) % HISTORY_SIZE;
 }else{
 itemCount++;
 }
 rear = (rear + 1) % HISTORY_SIZE;
 history[rear] = line;
}
// Function to tokenize a raw command as a String (line parameter)
void tokenizeExecute(char *line, int flag){
 char *args[ARGS_LIMIT];
 char *temp;
 temp = strdup(line);
 char *token;
 
 // Find the number of piped commands
 int i = 0;
 int pipeCount = 0;
 int _ =0;
 for ( _ = 0; line[_] != '\0' ; _++){
 if (line[_] == '|'){
 pipeCount++;
 
 }
 }
 
 //This helps with parsing
 if (temp[_-1] == '\n'){
 temp[_-1] = '\0';
 }
 // If there are any piped commands, then execute accordingly
 if (pipeCount > 0){
 // Parse entire piped commands into args
 while((token = strtok_r(temp, "|", &temp))){
 args[i] = strdup(token);
 i++;
 }
 args[i] = NULL;
 
 // Execute the piped commands by calling execute_pipes and then add the entire command to history
 execute_pipes(args, i);
 insert(strdup(line));
 }else{
 // If there are no pipes, then simply tokenize the command and call execute() to execute it
 token = (strtok(line, " \n"));
 while (token !=NULL){
 args[i] = token;
 token = strtok(NULL, " \n");
 i++;
 }
 args[i] = NULL;
 
 execute(args);
 if (args[0] != NULL && flag != 1){
 if (strcmp(args[0], "history")==0){
 if (args[1] != NULL){
 if (strcmp(args[1], "-c") != 0){
 insert(strdup(temp));
 }
 }
 }else{
 insert(strdup(temp));
 }
 }
 }
}
// Main function
int main(){ 
 char *line = NULL;
 size_t len = 0; 
 
 while (1){
 // Print prompt
 printf("sish> ");
 fflush(stdout);
 fflush (stdin);
 
 // Get command input with getline, exiting program if we receive no input
 int input = getline(&line, &len, stdin);
 if (input == -1){
 break;
 }
 
 // Execute command found
 tokenizeExecute(line, 0);
 }
}
