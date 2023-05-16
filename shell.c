#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int main()
{
        char *buffer = "($) ";
      	ssize_t input;
	char *line = NULL;
	size_t len = 0;
	char **argv;
	pid_t pid;
	int status, i = 0;

	while (1)
	{
		write(STDOUT_FILENO, buffer, 3);
		input = getline(&line, &len, stdin);
		if (input == -1)
		{	write(1,"\n", 1);
			break;
		}
		pid = fork();
		if (pid == -1)
		{	perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			argv = malloc(sizeof(char) * input);
			argv[0] = strtok (line, " \n");
			while (argv[i])
			{	i++;
				argv[i] = strtok (NULL, " \n");
			}
			execve(argv[0], argv, NULL);
			perror("Error:");
			exit(EXIT_FAILURE);
		}
		else 
			waitpid(pid, &status, 0);
		
	}
	return (0);
}
