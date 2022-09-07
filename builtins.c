#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <signal.h>

void (*get_builtins_func(char *s))(char **, char *, char *, char **, int)
{
	built_ins bi[] = {
		{"env", env_},
		{"exit", exit_},
		{"help", help_},
		{NULL, NULL}
	};
	int i = 0, j = 0, flag = 1, len1 = 0, len2 = 0;

	while (i < 3)
	{
		flag = 1;
		len1 = _strlen(s);
		len2 = _strlen(bi[i].name);
		if (len1 == len2)
		{
			j = 0;
			while (s[j] != '\0')
			{
				if (s[j] == bi[i].name[j])
					j++;
				else
				{
					flag = 0;
					break;
				}
			}
			if (flag == 1)
				return (*(bi[i]).f);
		}
		i++;
	}
	return (NULL);
}

void env_(char **array_buf, char *buf, char *path_str, char **array_path,
	  int exit_status)
{
	int i = 0;

	(void)path_str;
	(void)array_path;
	(void)exit_status;
	for (i = 0; environ[i]; i++)
		_print(environ[i]), _print("\n");
	free(array_buf);
	free(buf);
}

void exit_(char **array_buf, char *buf, char *path_str, char **array_path,
	   int exit_status)
{
	free(path_str);
	free(array_path);
	free(array_buf);
	free(buf);
	exit(exit_status);
}

void help_(char **array_buf, char *buf, char *path_str, char **array_path,
int exit_status)
{
	int status_env = 0, status_exit = 0, status_help = 0;

	(void)path_str;
	(void)array_path;
	(void)exit_status;
	if (array_buf[1])
	{
		status_env = _strcmp(array_buf[1], "env");
		status_exit = _strcmp(array_buf[1], "exit");
		status_help = _strcmp(array_buf[1], "help");
		if (status_env == 0)
			_print("Help page for env\n");
		if (status_exit == 0)
			_print("Help page for exit\n");
		if (status_help == 0)
			_print("Help page for help\n");
		else if (status_env == 1 && status_exit == 1 && status_help == 1)
			_print("Help page not found\n");
	}
	else
		_print("General help page\n");
	free(array_buf);
	free(buf);
}
