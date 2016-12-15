#include "shell.h"

/**
 * create_envlist - creates a linked list with all environment
 * variables in the extern environ variable
 */

env_t *create_envlist(void)
{
	env_t *head;
	int i;

	head = NULL;
	for (i = 0; environ[i] != NULL; i++)
		add_env(&head, environ[i]);
	return (head);
}

/**
 * add_env - adds another environmental variable to the beginning
 * of the environemental variable linked list
 * @head: head of the linked list
 * @env: environmental variable value to store
 * Return: the address of the new element, or NULL if it failed
 */

env_t *add_env(env_t **head, const char *env)
{
	env_t *new_node;
	env_t *temp;

	new_node = safe_malloc(sizeof(env_t));
	new_node->value = strdup(env);
	new_node->next = NULL;
	if (*head == NULL)
		*head = new_node;
	else
	{
		temp = *head;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new_node;
	}
	return (new_node);
}

/**
 * remove_env - removes an environmental variable
 * @head: pointer to the head of the linked list
 * @index: the nth node to delete
 */

void remove_env(env_t **head, int index)
{
	env_t *temp;
	env_t *dnode;
	int i;

	i = 0;
	temp = *head;
	if (index == 0)
	{
		*head = (*head)->next;
		_free(temp);
	}
	else
	{
		while (i < index - 1)
		{
			printf("im going into the loop");
			temp = temp->next;
			i++;
		}
		dnode = temp;
		dnode = dnode->next;
		temp->next = dnode->next;
		_free(dnode);
	}
}


/**
 * print_env - prints all environmental variables and its values
 * @head: head pointer to the linked list
 */

void print_env(env_t *head)
{
	while (head != NULL)
	{
		printf("%s\n", head->value);
		head = head->next;
	}
}
