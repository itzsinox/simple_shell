#include "shell.h"
#include "vars.h"
#include "main.h"
#include "lists.h"
#include "lists1.h"
#include "memory.h"
#include "parser.h"
#include "realloc.h"
#include "shell_loop.h"
#include "string.h"
#include "string1.h"
#include "tokenizer.h"
#include "builtin.h"
#include "environ.h"
#include "errors.h"
#include "errors1.h"
#include "exits.h"
#include "getLine.h"
#include "getenv.h"
#include "getinfo.h"
#include "history.h"
#include "_atoi.h"

/*
#include "reaf.h"
#include "shlf.h"
#include "strf.h"
#include "strf1.h"
#include "tof.h"
#include "vaf.h"
#include "buf.h"
#include "enf.h"
#include "erf.h"
#include "erf1.h"
#include "exf.h"
#include "glf.h"
#include "gvf.h"
#include "gif.h"
#include "hif.h"
#include "atf.h"
#include "mf.h"
#include "lif1.h"
#include "memf.h"
#include "paf.h"
#include "lif.h"
*/

/**
 * unset_alias - set alias
 * @info: struct
 * @str: str
 * Return: 0 or 1
 */

int unset_alias(info_t *info, char *str)
{
	char *p, c;
	int ret;

	p = _strchr(str, '=');

	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * _myhistory - to display the history list
 * @info: Structure
 * Return: 0
*/
int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * print_alias - print string
 * @node: node
 * Return: 0 or 1
*/
int print_alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
		_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * set_alias - set string
 * @info: struct
 * @str: str
 * Return: 0 or 1
*/
int set_alias(info_t *info, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
    * _myalias - alias
    * @info: Structure
    * Return: 0
*/
int _myalias(info_t *info)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		p = _strchr(info->argv[i], '=');
		if (p)
			set_alias(info, info->argv[i]);
		else
			print_alias(node_starts_with(info->alias, info->argv[i], '='));
	}

	return (0);
}
