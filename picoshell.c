#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

int picoshell(char **cmds[])
{
	size_t i = 0;
	int fd[2];
	int in_fd = 0;
	int ret = 0;
	int pid;
	int stat;

	while (cmds[i])
	{
		if (cmds[i + 1]) // parsing
		{
			if (pipe(fd) < 0)
				return 1;
		}
		else // last command should set the fds to -1 but why?
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
			if (in_fd) // antecipation for next loops
			{
				if (dup2(in_fd, 0) < 0)
					exit(1);
				close(in_fd);
			}
			if (fd[1] != -1) // last command fail save
			{
				if (dup2(fd[1], 1) < 0)
					exit(1);
				close(fd[1]);
				close(fd[0]);
			}
			execvp(cmds[i][0], cmds[i]);
			exit(1); // exec fail
		}
		else //parent
		{
			if (in_fd)
				close(in_fd);
			if (fd[1] != -1)
				close(fd[1]);
			in_fd = fd[0];
			i++;
		}
	}
	while (wait(&stat) > 0)
	{
		if (WIFEXITED(stat) && WEXITSTATUS(stat))
			ret = 1;
		else if (!WIFEXITED(stat))
			ret = 1;
	}
	return ret; // 0 for success, 1 for failure
}
