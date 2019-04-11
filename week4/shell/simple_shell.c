#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_LEN 100 /* The maximum length command */
char *divide(char *);

int main(void) {
  char *args[MAX_LEN / 2 + 1]; /* command line arguments */
  int should_run = 1;          /* flag to determine when to exit program */
  int background = 0;
  char* res; //strtok 결과 배열 저장
  pid_t pid;

  pid = fork();
  

  while (should_run) {
    printf("my_shell> ");
    fflush(stdout);
    /**
     * 표준입출력으로부터 문자열을 입력 받은 후:
     * (1) fork()를 통해 자식 프로세스를 생성
     * (2) 자식 프로세스가 execvp()를 호출하도록 할 것
     * (3) 만약 입력받은 문자에 &가 포함되어 있으면,
     *     부모 프로세스는 wait() 호출하지 않음
     */

    char *input = (char*)malloc(MAX_LEN*sizeof(char));
    fgets(input, MAX_LEN, stdin);
    if(pid < 0){
      fprintf(stderr, "Fork failed");
      return 1;
    } else if(pid == 0) {
      printf("=========================================\n");
      printf("CHILD : %s command",input);
      res = divide(*input);
      printf(res[0]);
    }else {
      wait(NULL);
    }

    free(input);
  }
  return 0;
}

char * divide(char *input){
  char *p; //포인터
  char *res;
  res = (char*)malloc(sizeof(char)*strlen(input)); //input크기만큼 동적할당

  p = strtok(input, "\n");
  while(p !=NULL) {
    int i = 0;
    //while을 돌면서 strtok 의 결과를 배열에 저장
    res[i] = p;

    p = strtok(NULL, "\n");
  }

  return res;
}
