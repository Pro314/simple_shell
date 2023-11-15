#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define MAX_INPUT_SIZE 1024
#define MAX_TOKEN_SIZE 64
#define MAX_NUM_TOKENS 64
void parse_input(char* input, char** tokens)
{
	char* token;
       	int token_count = 0; 
	
	/* Use strtok to split the input string into tokens*/
	token = strtok(input, " \n"); 
	while (token != NULL)
       	{
	       	tokens[token_count] = token; 
		token_count++;
		token = strtok(NULL, " \n"); 
	}
       
	tokens[token_count] = NULL; // Set the last token as NULL 
}

int main() 
{ 
	char input[MAX_INPUT_SIZE];
       	char* tokens[MAX_NUM_TOKENS];
       	while (1)
       	{ 
		printf("$ ");
		/* Prompt the user for a command*/
	       	fflush(stdout);
	       
		/* Read the input from the user*/
	       fgets(input, MAX_INPUT_SIZE, stdin);
	      
	       /* Parse the input into tokens*/
	       parse_input(input, tokens);
	       /* Fork a child process to execute the command*/
	       pid_t pid = fork();
	       if (pid < 0)
	       { 
		       printf("Fork failed!\n");
		       return 1;
	       }
	       if (pid == 0)
	       {
		       /* Child process*/
		       execvp(tokens[0], tokens);
		       printf("Command not found.\n");
		       return 0;
	       }
	       else
	       {
		       /* Parent process*/
		       wait(NULL);
	       }
	}

/*Print Environment variables*/

void main(int argc, char *argv[], char * envp[])
{
    int i;

    for (i = 0; envp[i] != NULL; i++)
    {
        printf("\n%s", envp[i]);
    }
}
	return 0;
}
