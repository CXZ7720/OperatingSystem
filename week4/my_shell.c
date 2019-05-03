#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_LEN 100 /* The maximum length command */

int main(void) {
  char *args[MAX_LEN / 2 + 1]; /* command line arguments */
  int should_run = 1;          /* flag to determine when to exit program */
  int background = 0;

  char *input;
  int status;

  while (should_run) {
    printf("my_shell> ");
    fflush(stdout);

    input = (char*)malloc(MAX_LEN*sizeof(char));
    fgets(input, MAX_LEN, stdin);

    int i = 0;
    args[i] = strtok(input, " \n");
    
    if (args[i] == NULL)
      goto no_input;

    if (strcmp(args[i], "exit") == 0) {
      // should_run = 0;
      // exit(0);
      break;
    }
    
    while (args[i] != NULL) {
      i++;
      args[i] = strtok(NULL, " \n");
    }

    if (strcmp(args[i-1], "&") == 0) {
      args[i - 1] = '\0';
      background = 1;
    }

    printf("background : %d\n", background);
    //test
    if(args[0] == "ls"){
      printf("YES");
    }


    pid_t pid = fork();
    if (pid < 0) {
      perror("Fork error");
      exit(0);
    }

    if (pid == 0) {
		execvp(args[0], args);
    }

    if (pid > 0) {
      if (!background) {
        waitpid(pid, NULL, 0);
      }
      printf("Waiting for Child process (pid: %d)\n", pid);
//      int retval = waitpid(pid, &status, 0);
      printf("Chid exits (status : %d)\n", status);

      //wait(NULL);
    } 
  no_input:;
  }
  free(input);
  return 0;
}
