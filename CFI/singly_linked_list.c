#include <stdio.h>
#include <stdlib.h>

struct s_list {
	int val;
	struct s_list *next;
};

typedef struct s_list slist_t;

static int get_node (slist_t **node, const int val)
{
	if (node == NULL)
		return -1;

	*node = malloc (sizeof (slist_t));
	if (*node == NULL) {
		printf ("malloc() failed.\n");
		return -1;
	}

	(*node)->val = val;
	(*node)->next = NULL;

	return 0;
}

static int insert_at_head (slist_t **head, slist_t **tail, 
		size_t *list_size, const int val)
{
	slist_t *node = NULL;
	int ret;

	ret = get_node (&node, val);
	if (ret < 0)
		return ret;

	if (*head != NULL)
		node->next = *head;
	else
		*tail = node;

	*head = node;

	*list_size = (*list_size + 1);

	return 0;
}

static int insert_at_tail (slist_t **head, slist_t **tail, 
		size_t *list_size, const int val)
{
	slist_t *node = NULL;
	int ret;

	ret = get_node (&node, val);
	if (ret < 0)
		return ret;

	if (*tail != NULL)
		(*tail)->next = node;

	*tail = node;

	*list_size = (*list_size + 1);

	return 0;
}

static int insert_after_nth (slist_t **head, slist_t **tail, 
		size_t *list_size, const int val, const size_t n)
{
	slist_t *node = NULL, *entry = NULL;
	int ret, i;

	if (n > *list_size)
	  return -1;

	if (n == 0)
		return insert_at_head (head, tail, list_size, val);
	else if (n == *list_size)
	       return insert_at_tail (head, tail, list_size, val);

	ret = get_node (&node, val);
	if (ret < 0)
		return ret;

	for (i = 0, entry = *head; i < n; i++)
		entry = entry->next;

	node->next = entry->next;
	entry->next = node;

	*list_size = (*list_size + 1);

	return 0;
}

/* will delete all nodes with 'val' */
static void delete_nodes (slist_t **head, 
		size_t *list_size, const int val)
{
	slist_t **curr = head;

	for ( ; *curr; ) {
		slist_t *entry = *curr;

		if (entry->val == val) {
			*curr = entry->next;
			free (entry);
			*list_size = (*list_size - 1);
		}
		else
			curr = &entry->next;
	}
}

static void print_list (slist_t **head)
{
	slist_t *entry = *head;

	printf ("======= List =======\n");

	while (entry != NULL) {
		printf ("%d\n", entry->val);
		entry = entry->next;
	}

	printf ("\n");
}

static void destroy_list (slist_t **head, slist_t **tail)
{
	slist_t *_head = *head;

	while (_head != NULL) {
		slist_t *node = _head;

		_head = _head->next;

		if (node)
			free (node);
	}

	*head = *tail = NULL;
}

int main()
{
	slist_t *head = NULL, *tail = NULL;
	size_t list_size = 0;
	int i, ret;

	for (i = 7; i > 0; i--) {
		ret = insert_at_head (&head, &tail, &list_size, i);
		if (ret < 0) {
			destroy_list (&head, &tail);
			return -1;
		}
	}

	print_list (&head);

	for (i = 8; i <= 10; i++) {
		ret = insert_at_tail (&head, &tail, &list_size, i);
		if (ret < 0) {
			destroy_list (&head, &tail);
			return -1;
		}
	}

	print_list (&head);

	ret = insert_after_nth (&head, &tail, &list_size, 11, 0);
	if (ret < 0) {
		destroy_list (&head, &tail);
		return -1;
	}

	print_list (&head);

	ret = insert_after_nth (&head, &tail, &list_size, 12, 11);
	if (ret < 0) {
		destroy_list (&head, &tail);
		return -1;
	}

	print_list (&head);

	ret = insert_after_nth (&head, &tail, &list_size, 13, 7);
	if (ret < 0) {
		destroy_list (&head, &tail);
		return -1;
	}

	print_list (&head);

	delete_nodes (&head, &list_size, 12);

	print_list (&head);

	destroy_list (&head, &tail);

	print_list (&head);

	return 0;
}
