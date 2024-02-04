#include "monty.h"

/**
 * open_file - opens a file
 * @file_name: the file namepath
 * Return: void
 */

void openFile(char *fileName)
{
	FILE *fd = fopen(fileName, "r");

	if (fileName == NULL || fd == NULL)
		err(2, fileName);

	readFile(fd);
	fclose(fd);
}

/**
 * readFile - reads a file
 * @fd: pointer to file descriptor
 * Return: void
 */

void readFile(FILE *fd)
{
	int line_num, format = 0;
	char *buff = NULL;
	size_t len = 0;

	for (line_num = 1; getline(&buff, &len, fd) != -1; line_num++)
	{
		format = parseLine(buff, line_num, format);
	}
	free(buff);
}

/**
 * parseLine - Separates each line into tokens to determine
 * which function to call
 * @buff: line from the file
 * @line_num: line number
 * @format:  storage format. If 0 Nodes will be entered as a stack.
 * if 1 nodes will be entered as a queue.
 * Return: Returns 0 if the opcode is stack. 1 if queue.
 */

int parseLine(char *buff, int line_num, int format)
{
	char *opcode, *value;
	const char *delim = "\n ";

	if (buff == NULL)
		err(4);

	opcode = strtok(buff, delim);
	if (opcode == NULL)
		return (format);
	value = strtok(NULL, delim);

	if (strcmp(opcode, "stack") == 0)
		return (0);
	if (strcmp(opcode, "queue") == 0)
		return (1);

	findFunc(opcode, value, line_num, format);
	return (format);
}

/**
 * findFunc - find the appropriate function for the opcode
 * @opcode: opcode
 * @value: argument of opcode
 * @format:  storage format. If 0 Nodes will be entered as a stack.
 * @line_num: line number
 * if 1 nodes will be entered as a queue.
 * Return: void
 */
void findFunc(char *opcode, char *value, int line_num, int format)
{
	int i;
	int flag;

	instruction_t func_list[] = {
		{"push", _push},
		{"pall", _pall},
		{"pint", print_top},
		{"pop", pop_top},
		{"nop", nop},
		{"swap", swap_nodes},
		{"add", add_nodes},
		{"sub", sub_nodes},
		{"div", div_nodes},
		{"mul", mul_nodes},
		{"mod", mod_nodes},
		{"pchar", print_char},
		{"pstr", print_str},
		{"rotl", rotl},
		{"rotr", rotr},
		{NULL, NULL}
	};

	if (opcode[0] == '#')
		return;

	for (flag = 1, i = 0; func_list[i].opcode != NULL; i++)
	{
		if (strcmp(opcode, func_list[i].opcode) == 0)
		{
			callFun(func_list[i].f, opcode, value, line_num, format);
			flag = 0;
		}
	}
	if (flag == 1)
		err(3, line_num, opcode);
}

/**
 * callFun - Calls the required function.
 * @function: Pointer to the function that is about to be called.
 * @op: string representing the opcode.
 * @val: string representing a numeric value.
 * @line_num: line numeber for the instruction.
 * @format: Format specifier. If 0 Nodes will be entered as a stack.
 * if 1 nodes will be entered as a queue.
 */
void callFun(op_func func, char *op, char *val, int line_num, int format)
{
	stack_t *node;
	int flag;
	int i;

	flag = 1;
	if (strcmp(op, "push") == 0)
	{
		if (val != NULL && val[0] == '-')
		{
			val = val + 1;
			flag = -1;
		}
		if (val == NULL)
			err(5, line_num);
		for (i = 0; val[i] != '\0'; i++)
		{
			if (isdigit(val[i]) == 0)
				err(5, line_num);
		}
		node = create_node(atoi(val) * flag);
		if (format == 0)
			func(&node, line_num);
		if (format == 1)
			add_to_queue(&node, line_num);
	}
	else
		func(&head, line_num);
}
