#ifndef BUF1_H
#define BUF1_H

/**
    * unset_alias - set alias
    * @info: struct
    * @str: str 
    * Return: 0 or 1
*/

int unset_alias(info_t *info, char *str)
{
char *x, y;
int r;

x = _strchr(str, '=');
if (!x)
return (1);
y = *x;
*x = 0;
r = delete_node_at_index(&(info->alias),
get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
*x = y;
return (r);
}

/**
    * _myhistory – to display the history list
    * @info: Structure
    * Return: 0
*/

int _myhistory(info_t *info)
{
print_list(info->history);
return (0);
}

/**
    * print_alias – print string
    * @node: node
    * 
    * Return: 0 or 1
*/

int print_alias(list_t *node)
{
char *x = NULL, *y = NULL;

if (node)
{
x = _strchr(node->str, '=');
for (y = node->str; y <= x; y++)
_putchar(*y);
_putchar('\'');
_puts(x + 1);
_puts("'\n");
return (0);
}
return (1);
}

/**
    * set_alias – set string
    * @info: struct
    * @str: str 
    * Return: 0 or 1
*/

int set_alias(info_t *info, char *str)
{
char *x;

x = _strchr(str, '=');
if (!x)
return (1);
if (!*++x)
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
int x = 0;
char *y = NULL;
list_t *n = NULL;

if (info->argc == 1)
{
n = info->alias;
while (n)
{
print_alias(n);
n = n->next;
}
return (0);
}
for (x = 1; info->argv[x]; x++)
{
y = _strchr(info->argv[x], '=');
if (y)
set_alias(info, info->argv[x]);
else
print_alias(node_starts_with(info->alias, info->argv[x], '='));
}
return (0);
}
#endif
