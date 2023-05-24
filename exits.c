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
#include "buf1.h"
#include "enf.h"
#include "erf.h"
#include "erf1.h"
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
* _strchr - locate char in str
* @s: str
* @c: char
* Return: ptr
*/
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
		return (s);
	} while (*s++ != '\0');

	return (NULL);
}

/**
* *_strncpy - copie str
* @dest: str destination
* @src: str source
* @n: amount of chars
* Return: concat str
*/
char *_strncpy(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
	{
		dest[j] = '\0';
		j++;
	}
	}
	return (s);
}

/**
* _strncat - concat 2 str
* @dest: 1st str
* @src: 2nd str
* @n: amount of bytes
* Return: concat str
*/
char *_strncat(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0' && j < n)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	if (j < n)
		dest[i] = '\0';
	return (s);
}
