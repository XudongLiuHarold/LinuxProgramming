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
	pid_t pid,_pid;
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
		printf("Child process running\n"); 
		sleep(5);
		exit(EXIT_SUCCESS);
	}
	else
	{
		printf("Parent Process before waiting\n");
		//If no loop wait, the parent will exit before the child.
		 while (1) {
            _pid = waitpid(pid, &status, WNOHANG); //No_Block
            if (_pid < 0) {
                perror("wait error");
            } else if (0 == _pid) {
                sleep(1);
            } else {
                break;
            }
        }

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
