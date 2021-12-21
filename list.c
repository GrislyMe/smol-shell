#include "list.h"

int append(node* head, node* next) {
	node* current = head;
	while(current->next)
		current = current->next;
	current->next = next;
	return 0;
}
