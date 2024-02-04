#include "monty.h"


/**
 * _push - Adds a node to the stack.
 * @newNode: Pointer to the new node.
 * @ln: Interger representing the line number of of the opcode.
 */
void _push(stack_t **newNode, __attribute__((unused))unsigned int line_num)
{
	stack_t *tmp;

	if (newNode == NULL || *newNode == NULL)
		exit(EXIT_FAILURE);
	if (head == NULL)
	{
		head = *newNode;
		return;
	}
	tmp = head;
	head = *newNode;
	head->next = tmp;
	tmp->prev = head;
}
