#ifndef EXF_H
#define EXF_H
/**
**_strchr – locate char in str
*@s: str
*@c: char
*Return: ptr
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
**_strncpy – copie str
*@dest: str destination
*@src: str source
*@n: amount of chars
*Return: concat str
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
**_strncat – concat 2 str
*@dest: 1st str
*@src: 2nd str
*@n: amount of bytes
*Return: concat str
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
#endif
