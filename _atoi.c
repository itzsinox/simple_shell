#include "shell.h"
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
#include "getLine.h"
#include "getenv.h"
#include "getinfo.h"
#include "history.h"
#include "vars.h"

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
#include "glf.h"
#include "gvf.h"
#include "gif.h"
#include "hif.h"
#include "mf.h"
#include "lif1.h"
#include "memf.h"
#include "paf.h"
#include "lif.h"
*/

/**
 * interactive - returns true if shell is interactive mode
 * @info: struct address
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - checks if character is a delimeter
 * @c: the char to check
 * @delim: the delimeter string
 * Return: 1 if true, 0 if false
 */
int is_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 *_isalpha - checks for alphabetic character
 *@c: The character to input
 *Return: 1 if c is alphabetic, 0 otherwise
 */

int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *_atoi - converts a string to an integer
 *@s: the string to be converted
 *Return: 0 if no numbers in string, converted number otherwise
 */

int _atoi(char *s)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0;  s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
