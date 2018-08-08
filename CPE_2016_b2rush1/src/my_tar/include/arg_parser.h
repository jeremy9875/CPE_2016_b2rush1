/*
** arg_parser.h for my_tar in /home/xeo/documents/CPE/CPE_2016_b2rush1/src/my_tar/include
** 
** Made by theo benbezza-grevet
** Login   <theo.benbezza-grevet@epitech.eu>
** 
** Started on  Sun Mar 05 22:10:25 2017 theo benbezza-grevet
** Last update Sun Mar 05 23:28:10 2017 theo benbezza-grevet
*/

#ifndef ARG_PARSER_H_
# define ARG_PARSER_H_

# include <stdbool.h>
# include "collection.h"

# define ARG_INVALID	("my_tar: invalid option -- '%c'\n")
# define ERROR_STR	("error with args:/\n")

typedef enum	s_options_enum
{
  op_extract = 1,
  op_create = 1 << 1,
  op_file = 1 << 2,
  op_list = 1 << 3,
}		t_op_enum;

typedef struct	s_option
{
  char		option_char;
  t_op_enum	option;
}		t_option;

typedef struct	s_arguments
{
  t_node	*files_head;
  int		options;
  const char	*file;
}		t_arguments;

bool		try_parse_args(int argc, char **argv, t_arguments *config);

#endif /* !ARG_PARSER_H_ */
