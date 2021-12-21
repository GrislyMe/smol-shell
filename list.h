typedef struct node {
	char str[256];
	struct node* next;
}node;

int append(node* head, node* next);
