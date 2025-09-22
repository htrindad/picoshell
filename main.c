#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

int picoshell(char **cmds[]);

int main(void)
{
	char **cmds[4];

//	static char *cmd1[] = {"cat", NULL};
//	static char *cmd2[] = {"cat", NULL};
//	static char *cmd3[] = {"ls", "-l", NULL};

	static char *cmd1[] = {"ls", NULL};
	static char *cmd2[] = {"grep", "l", NULL};
	static char *cmd3[] = {"wc", NULL};//essayer commande inexistante (comme "wololo")

	cmds[0] = cmd1;
	cmds[1] = cmd2;
	cmds[2] = cmd3;
	cmds[3] = NULL;
	
	int res = picoshell(cmds);
	if (res)
		write(1, "Returned 1\n", 11);
	return (0);
}
