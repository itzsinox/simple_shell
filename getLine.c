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
#include "builtin1.h"
#include "environ.h"
#include "errors.h"
#include "errors1.h"
#include "exits.h"
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
#include "buf1.h"
#include "enf.h"
#include "erf.h"
#include "erf1.h"
#include "exf.h"
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
 * sigintHandler - block ctrl-C
 * @sig_num: signal number
 * Return: void
*/

void sigintHandler(__attribute__((unused))int sig_num)
{

	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}

/**
 * input_buf - buffer
 * @info: info
 * @buf: buff
 * @len: len
 * Return: bytes
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		r = getline(buf, &len_p, stdin);
#else
		r = _getline(info, buf, &len_p);
#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0';
				r--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			{
				*len = r;
				info->cmd_buf = buf;
			}
		}
	}
	return (r);
}

/**
 * get_input - line minus new line
 * @info: info
 * Return: bytes
 */
ssize_t get_input(info_t *info)
{
	static char *buf;
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	r = input_buf(info, &buf, &len);
	if (r == -1)
		return (-1);
	if (len)
	{

		j = i;
		p = buf + i;

		check_chain(info, buf, &j, i, len);
		while (j < len)
		{
			if (is_chain(info, buf, &j))
				break;
			j++;
		}

		i = j + 1;
		if (i >= len)
		{
			i = len = 0;
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p;
		return (_strlen(p));
	}

	*buf_p = buf;
	return (r);
}

/**
 * read_buf - read buff
 * @info: parameter struct
 * @buf: buffer
 * @i: size
 * Return: r
*/
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(info->readfd, buf, READ_BUF_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * _getline - get next line
 * @info: parameter struct
 * @ptr: ptr’s address
 * @length: size of preallocated ptr
 * Return: s
*/
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = read_buf(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);

	if (s)

		_strncat(new_p, buf + i, k - i);
	else
		_strncpy(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}
