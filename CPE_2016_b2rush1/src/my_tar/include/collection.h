/*
** collection.h for my_tar in /home/xeo/documents/CPE/CPE_2016_b2rush1/src/my_tar/include
** 
** Made by theo benbezza-grevet
** Login   <theo.benbezza-grevet@epitech.eu>
** 
** Started on  Sun Mar 05 22:23:49 2017 theo benbezza-grevet
** Last update Sun Mar 05 22:24:13 2017 theo benbezza-grevet
*/

#ifndef collection_h_
# define collection_h_

# include <stddef.h>

typedef struct	s_node
{
  void		*data;
  struct s_node	*prev;
  struct s_node	*next;
}		t_node;

t_node		*list_add_end(t_node **head, void *data);

size_t		collection_size(const t_node *head);
void		collection_destroy(t_node *head);

#endif /* !collection_h_ */
