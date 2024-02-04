#include "monty.h"
/**
 * _pall - print all the values of the stack.
 * @stack_all: Pointer to a pointer pointing to top node of the stack.
 * @line_num: line number of  the opcode.
 */
void _pall(stack_t **stack_all, unsigned int line_num)
{
	stack_t *current;

	(void) line_num;
	if (stack_all == NULL)
		exit(EXIT_FAILURE);
	current = *stack_all;
	while (current != NULL)
	{
		printf("%d\n", current->n);
		current = current->next;
	}
}
