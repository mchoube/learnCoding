#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

static size_t is_loop (slist_t **head)
{
	slist_t *entry = (*head)->next;

	while (entry) {
		if (entry == *head)
			return 1;

		entry = entry->next;
	}

	return 0;
}

int main()
{
	slist_t *head = NULL, *tail = NULL;
	size_t list_size = 0;
	int i, ret;
	time_t t;

	time (&t);

	srand (t);

	for (i = 13; i > 0; i--) {
		ret = insert_at_head (&head, &tail, &list_size, (rand() % 10));
		if (ret < 0) {
			destroy_list (&head, &tail);
			return -1;
		}
	}

	print_list (&head);

	/* tail->next = head; */

	printf ("loop: %d\n", is_loop (&head));

	destroy_list (&head, &tail);

	print_list (&head);

	return 0;
}
