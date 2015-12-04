#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>

static void pr_ids(char * );
static void pre_exit(int status);

int main(int argc, char const *argv[])
{
	pid_t pid;
	int status;

	if ((pid = fork()) < 0)
	{
	 perror("fork error");
	 return -1;
	}
	else if (0 == pid)
	{
		printf("Child process\n");
		pr_ids("child");
		sleep(5);
		exit(EXIT_SUCCESS);
	}
	else
	{
		printf("Parent Process before waiting\n");
		waitpid(pid,&status,WUNTRACED); // block 

		printf("Parent Process After waiting\n");
		printf("Parent process\n");
		pr_ids("Parent");
	}
	return 0;
}

static void pr_ids(char* name)
{
		printf("%s:pid= %d, ppid = %d ,pgrp = %d\n",name,getpid(),getppid(),getpgrp());
		fflush(stdout);
}

static void pre_exit(int status) {
    if (WIFEXITED(status))
        printf("normal termination, exit status=%d\n", WEXITSTATUS(status));
    else if (WIFSIGNALED(status))
        printf("abnormal termination, signal number=%d%s\n", WTERMSIG(status), WCOREDUMP(status) ? "(core file generated)" : "");
    else if (WIFSTOPPED(status))
        printf("child stopped, signal number=%d\n", WSTOPSIG(status));
}
