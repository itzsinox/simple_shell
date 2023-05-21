#include "shell.h"

/**
 * check_chain - check chaining
 * @info: info
 * @buf: char buf
 * @p: address of cur pos
 * @i: starting pos
 * @len: len
 * Return: void
 */

void check_chain(info_t *info, char *buf,
		size_t *p, size_t i, size_t len)
{
	size_t x = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			x = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			x = len;
		}
	}
	*p = x;
}

/**
 * is_chain - test curr char
 * @info: info
 * @buf: char
 * @p: address
 * Return: 1 or 0
 */
int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t x = *p;

	if (buf[x] == '|' && buf[x + 1] == '|')
	{
		buf[x] = 0;
		x++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[x] == '&' && buf[x + 1] == '&')
	{
		buf[x] = 0;
		x++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[x] == ';')
	{
		buf[x] = 0;
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = x;
	return (1);
}

/**
 * replace_vars - replace vars
 * @info: info
 * Return: 1 or 0
 */
int replace_vars(info_t *info)
{
	int x = 0;
	list_t *n;

	for (x = 0; info->argv[x]; x++)
	{
		if (info->argv[x][0] != '$' || !info->argv[x][1])
			continue;
		if (!_strcmp(info->argv[x], "%?"))
		{
			replace_string(&(info->argv[x]),
					_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[x], "$$"))
		{
			replace_string(&(info->argv[x]),
					_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		n = node_starts_with(info->env, &info->argv[x][1], '=');
		if (n)
		{
			replace_string(&(info->argv[x]),
					_strdup(_strchr(n->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[x], _strdup(""));
	}
	return (0);
}

/**
 * replace_alias - replace alias
 * @info: info
 * Return: 1 or 0
 */
int replace_alias(info_t *info)
{
	int x;
	list_t *n;
	char *p;

	for (x = 0; x < 10; x++)
	{
		n = node_starts_with(info->alias, info->argv[0], '=');
		if (!n)
			return (0);
		free(info->argv[0]);
		p = _strchr(n->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * replace_string - replace str
 * @old: address of old str
 * @new: new str
 * Return: 1 or 0
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
