#include "shell.h"

/**
 * is_cmd - det if file is executable
 * @info: info struct
 * @path: path
 * Return: 1 or 0
 */
int is_cmd(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);
	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * find_path - find cmd
 * @info: info struct
 * @pathstr: path str
 * @cmd: cmd to find
 * Return: full path
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int i = 0, cu_p = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = dup_chars(pathstr, cu_p, i);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(info, path))
				return (path);
			if (!pathstr[i])
				break;
			cu_p = i;
		}
		i++;
	}
	return (NULL);
}
