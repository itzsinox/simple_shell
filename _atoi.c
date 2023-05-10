
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
	int i, sg = 1, f = 0, op;
	unsigned int res = 0;

	for (i = 0; s[i] != '\0' && f != 2; i++)
	{
		if (s[i] == '-')
			sg *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			f = 1;
			res *= 10;
			res += (s[i] - '0');
		}
		else if (f == 1)
			f = 2;
	}

	if (sg == -1)
		op = -res;
	else
		op = res;

	return (op);
}
