#include "shell.h"

/**
 * add_node_end - add node
 * @head: ptr's address
 * @str: str
 * @num: node idx
 * Return: size
 */
list_t *add_node_end(list_t **head, const char *str, int num)
{
	list_t *n_node, *node;

	if (!head)
		return (NULL);
	node = *head;
	n_node = malloc(sizeof(list_t));
	if (!n_node)
		return (NULL);
	_memset((void *)n_node, 0, sizeof(list_t));
	n_node->num = num;
	if (str)
	{
		n_node->str = _strdup(str);
		if (!n_node->str)
		{
			free(n_node);
			return (NULL);
		}
	}
	if (node)
	{
		do {(node->next);
			node = node->next;
			node->next = n_node;
		} while (node->next);
	}
	else
		*head = n_node;
	return (n_node);
}

/**
 * add_node - add node
 * @head: ptr's address
 * @str: str
 * @num: index node
 * Return: size
 */
list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *n_head;

	if (!head)
		return (NULL);
	n_head = malloc(sizeof(list_t));
	if (!n_head)
		return (NULL);
	_memset((void *)n_head, 0, sizeof(list_t));
	n_head->num = num;
	if (str)
	{
		n_head->str = _strdup(str);
		if (!n_head->str)
		{
			free(n_head);
			return (NULL);
		}
	}
	n_head->next = *head;
	*head = n_head;
	return (n_head);
}

/**
 * delete_node_at_index - delete node
 * @head: ptr's address
 * @index: index
 * Return: 1 or 0
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
	list_t *n, *p_n;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);
	if (!index)
	{
		n = *head;
		*head = (*head)->next;
		free(n->str);
		free(n);
		return (1);
	}
	n = *head;
	do {
		if (i == index)
		{
			p_n->next = n->next;
			free(n->str);
			free(n);
			return (1);
		}
		i++;
		p_n = n;
		n = n->next;
	} while (n);
	return (0);
}

/**
 * print_list_str - print str of a list_t
 * @h: ptr
 * Return: size
 */
size_t print_list_str(const list_t *h)
{
	size_t i = 0;

	do {
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		i++;
	} while (h);
	return (i);
}

/**
 * free_list - free nodes
 * @head_ptr: ptr's address
 * Return: void
 */
void free_list(list_t **head_ptr)
{
	list_t *n, *n_n, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	n = head;
	while (n)
	{
		n_n = n->next;
		free(n->str);
		free(n);
		n = n_n;
	}
	*head_ptr = NULL;
}
