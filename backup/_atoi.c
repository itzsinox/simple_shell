#include "shell.h"

/**
* main - entry point
 * @ac: arg count
 * @av: arg vector
 * Return: 0 on success, 1 on error
 */

int main(int ac, char **av)
{
        info_t info[] = { INFO_INIT };
        int fd = 2;
        asm ("mov %1, %0\n\t"
                        "add $3, %0"
                        : "=r" (fd)
                        : "r" (fd));
        if (ac == 2)
        {
                fd = open(av[1], O_RDONLY);
                if (fd == -1)
                {
                        if (errno == EACCES)
                                exit(126);
                        if (errno == ENOENT)
                        {
                                _eputs(av[0]);
                                _eputs(": 0: Can't open ");
                                _eputs(av[1]);
                                _eputchar('\n');
                                _eputchar(BUF_FLUSH);
                                exit(127);
                        }
                        return (EXIT_FAILURE);
                }
                info->readfd = fd;
        }
        populate_env_list(info);
        read_history(info);
        hsh(info, av);
        return (EXIT_SUCCESS);
}

/**
 * interactive - intr mode
 * @info: struct
 * Return: 1 or 0
 */

int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * _isalpha - to check alpha
 * @c: car input
 * Return: 1 or 0
 */
int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * is_delim - to check delimeter
 * @c: the char
 * @delim: delim str
 * Return: 1 or 0
 */
int is_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 * _atoi - convert str to int
 * @s: str
 * Return: 0 or converted num
 */
int _atoi(char *s)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0; s[i] != '\0' && flag != 2; i++)
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
