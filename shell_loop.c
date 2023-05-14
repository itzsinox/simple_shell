#include "shell.h"

/**
 * find_builtin - find builtin com
 * @info: info
 * Return: -1, 0, 1 or 2
 */
int find_builtin(info_t *info)
{
	int i, buil_ret = -1;
	builtin_table butab[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (i = 0; butab[i].type; i++)
		if (_strcmp(info->argv[0], butab[i].type) == 0)
		{
			info->line_count++;
			buil_ret = butab[i].func(info);
			break;
		}
	return (buil_ret);
}

/**
 * hsh - main shell loop
 * @info: info
 * @av: arg vect
 * Return: 0 or 1 or error
 */
int hsh(info_t *info, char **av)
{
	ssize_t r = 0;
	int buil_ret = 0;

	do {
		clear_info(info);
		if (interactive(info))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		r = get_input(info);
		if (r != -1)
		{
			set_info(info, av);
			buil_ret = find_builtin(info);
			if (buil_ret == -1)
				find_cmd(info);
		}
		else if (interactive(info))
			_putchar('\n');
		free_info(info, 0);
	} while (r != -1 && buil_ret != -2);
	write_history(info);
	free_info(info, 1);
	if (!interactive(info) && info->status)
		exit(info->status);
	if (buil_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (buil_ret);
}

/**
 * find_cmd - find com in path
 * @info: info
 * Return: void
 */
void find_cmd(info_t *info)
{
	char *path = NULL;
	int x, y;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (x = 0, y = 0; info->arg[x]; x++)
		if (!is_delim(info->arg[x], " \t\n"))
			y++;
	if (!y)
		return;
	path = find_path(info, _getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_cmd(info);
	}
	else
	{
		if ((interactive(info) || _getenv(info, "PATH=")
					|| info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
			fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}

/**
 * fork_cmd - fork exc thread to run cmd
 * @info: info
 * Return: void
 */
void fork_cmd(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "permission denied\n");
		}
	}
}
