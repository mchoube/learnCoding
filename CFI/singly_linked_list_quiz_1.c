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

static void remove_3rd_last(slist_t **head, size_t *list_size)
{
	slist_t **curr = head;

	for ( ; *curr; ) {
		slist_t *entry = *curr;

		if (entry->next != NULL
			&& entry->next->next != NULL 
			&& entry->next->next->next == NULL) {

			*curr = entry->next;
			free (entry);
			*list_size = (*list_size - 1);

			return;
		}
		else
			curr = &entry->next;
	}
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

	for (i = 10; i > 0; i--) {
		ret = insert_at_head (&head, &tail, &list_size, i);
		if (ret < 0) {
			destroy_list (&head, &tail);
			return -1;
		}
	}

	print_list (&head);

	remove_3rd_last(&head, &list_size);

	print_list (&head);

	destroy_list (&head, &tail);

	print_list (&head);

	return 0;
}
