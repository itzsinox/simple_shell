#include "shell.h"

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
    * get_input – line (–) new line
    * @info: parameter struct
    * Return: read bytes
*/
ssize_t get_input(info_t *info)
{
	static char *buf;
	static size_t x, y, l;
	ssize_t r = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	r = input_buf(info, &buf, &l);
	if (r == -1)
		return (-1);
	if (l)
	{

		y = x;
		p = buf + x;

		check_chain(info, buf, &y, x, l);
		while (y < l)
		{
			if (is_chain(info, buf, &y))
				break;
			y++;
		}

		x = y + 1;
		if (x >= l)
		{
			x = l = 0;
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p;
		return (_strlen(p));
	}

	*buf_p = buf;
	return (r);
}

/**
    * input_buf - buffer
    * @info: parameter struct
    * @buf: buffer’s address
    * @len: len’s address
    * Return: read bytes
*/
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t x = 0;
	size_t l_p = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		x = getline(buf, &l_p, stdin);
#else
		x = _getline(info, buf, &l_p);
#endif
		if (x > 0)
		{
			if ((*buf)[x - 1] == '\n')
			{
				(*buf)[x - 1] = '\0';
				x--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			{
				*len = x;
				info->cmd_buf = buf;
			}
		}
	}
	return (x);
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
    * _getline – get next line
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
	if (!new_p) /* MALLOC FAILURE! */
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
