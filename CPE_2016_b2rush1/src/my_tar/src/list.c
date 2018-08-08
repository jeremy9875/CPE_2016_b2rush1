/*
** list.c for my_tar in /home/xeo/documents/CPE/CPE_2016_b2rush1/src/my_tar/src
** 
** Made by theo benbezza-grevet
** Login   <theo.benbezza-grevet@epitech.eu>
** 
** Started on  Sun Mar 05 22:24:25 2017 theo benbezza-grevet
** Last update Sun Mar 05 23:04:47 2017 theo benbezza-grevet
*/

#include <stdlib.h>
#include "collection.h"

t_node		*list_add_end(t_node **head, void *data)
{
  t_node	*new_node;
  t_node	*current;

  if (!(new_node = malloc(sizeof(t_node))))
    return (NULL);
  new_node->data = data;
  new_node->next = NULL;
  if (!*head)
  {
    new_node->prev = NULL;
    *head = new_node;
  }
  else
  {
    current = *head;
    while (current->next)
      current = current->next;
    current->next = new_node;
    new_node->prev = current;
  }
  return (new_node);
}

void		collection_destroy(t_node *head)
{
  t_node	*current;
  t_node	*tmp;

  current = head;
  while (current)
  {
    tmp = current->next;
    free(current);
    current = tmp;
  }
}

size_t		collection_size(const t_node *head)
{
  size_t	size;

  size = 0;
  while (head)
  {
    size++;
    head = head->next;
  }
  return (size);
}
