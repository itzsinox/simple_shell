#include "shell.h"

/**
 * _strcmp - perform lexicographic
 * @s1: 1st str
 * @s2: 2nd str
 * Return: -, + or 0
 */
int _strcmp(char *s1, char *s2)
{
	do {
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	} while (*s1 && *s2);
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * _strlen - length of str
 * @s: str
 * Return: int
 */
int _strlen(char *s)
{
	int i = 0;

	if (!s)
		return (0);
	while (*s++)
		i++;
	return (i);
}

/**
 * _strcat - concat 2 str
 * @dest: dest buff
 * @src: src buff
 * Return: ptr
 */
char *_strcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}

/**
 * starts_with - check haystack
 * @haystack: str
 * @needle: sub string
 * Return: address
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}
