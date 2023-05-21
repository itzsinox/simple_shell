#include "shell.h"

/**
 * ffree - free str
 * @pp: str of str
 */
void ffree(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a);
}

/**
 * _memset - fill memory
 * @s: ptr
 * @b: byte
 * @n: amount of bytes
 * Return: ptr
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		s[i] = b;
	return (s);
}

/**
 * _realloc - realloc a block
 * @ptr: ptr
 * @old_size: size of prev block
 * @new_size: size of new block
 * Return: ptr
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);
	p = malloc(new_size);
	if (!p)
		return (NULL);
	old_size = old_size < new_size ? old_size : new_size;
	do {
		p[old_size] = ((char *)ptr)[old_size];
	} while (old_size--);
	free(ptr);
	return (p);
}
