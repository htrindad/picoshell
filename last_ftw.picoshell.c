#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

int ftw_picoshell(char **cmds[])
{
	int fd[2];
	int in_fd = 0;
	int ret = 0;
	int pid;
	int stat;

	for (size_t i = 0; cmds[i]; i++)
	{
		if (cmds[i + 1]) // parsing
		{
			if (pipe(fd) < 0)
				return 1;
		}
		else // last command sets the fds to -1 so that it may write the execvp back to the terminal
		{
			fd[0] = -1;
			fd[1] = -1;
		}
		pid = fork();
		if (pid < 0) // err handle
		{
			for (size_t j = 0; j < 2; j++)
				if (fd[j] < 0)
					close(fd[j]);
			if (in_fd < 0)
				close(in_fd);
			return 1;
		}
		if (!pid) // child process
		{
			if (in_fd) // antecipation for next loops. The very first iteration does not need a dup2 due to what is written in fd[1] getting to fd[0]
			{
				if (dup2(in_fd, 0) < 0)
					exit(1);
				close(in_fd);
			}
			if (fd[1] != -1) // last command fail safe
			{
				if (dup2(fd[1], 1) < 0)
					exit(1);
				close(fd[1]);
				close(fd[0]); // fd[0] is closed either way
			}
			execvp(cmds[i][0], cmds[i]);
			exit(1); // exec fail
		}
		if (in_fd) // parent
			close(in_fd);
		if (fd[1] != -1)
			close(fd[1]);
		in_fd = fd[0]; // this sets to fd[0] but said fd is closed.
	}
	while (wait(&stat) > 0) //necessary so that te processes stop
	{
		if (WIFEXITED(stat) && WEXITSTATUS(stat)) // check for anomalies
			ret = 1;
		else if (!WIFEXITED(stat))
			ret = 1;
	}
	return ret; // 0 for success, 1 for failure
}
