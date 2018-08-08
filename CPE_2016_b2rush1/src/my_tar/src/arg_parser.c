/*
** arg_parser.c for my_tar in /home/xeo/documents/CPE/CPE_2016_b2rush1/src/my_tar/src
** 
** Made by theo benbezza-grevet
** Login   <theo.benbezza-grevet@epitech.eu>
** 
** Started on  Sun Mar 05 22:14:00 2017 theo benbezza-grevet
** Last update Sun Mar 05 23:15:59 2017 theo benbezza-grevet
*/

#include <stdio.h>
#include <string.h>
#include "arg_parser.h"

static const t_option	options[] =
{
  { 'x', op_extract },
  { 'c', op_create },
  { 'f', op_file },
  { 't', op_list },
};

static t_op_enum	get_option(char op)
{
  int			index;
  int			max;
  const t_option	*option;

  index = 0;
  max = sizeof(options) / sizeof(t_option);
  while (index < max)
  {
    option = &options[index++];
    if (option->option_char == op)
      return (option->option);
  }
  return (0);
}

int	try_parse_options(const char *str, int *opt_flags)
{
  int	option;
  int	options;

  options = 0;
  while (*str)
  {
    if (*str == '-')
      continue ;
    option = get_option(*str);
    if (option == 0)
    {
      fprintf(stderr, ARG_INVALID, *str);
      return (options);
    }
    *opt_flags |= option;
    options |= option;
    str++;
  }
  return (option);
}

bool	try_parse_file(char *str, t_node **files_head)
{
  list_add_end(files_head, str);
  return (true);
}

bool	try_parse_args(int argc, char **argv, t_arguments *config)
{
  int	index;
  int	options;

  if (argc < 3)
    return (false);
  index = 1;
  while (index < argc)
  {
    if (index == 1 || argv[index][0] == '-')
    {
      if (!(options = try_parse_options(argv[index], &config->options)))
        return (false);
      if (options & op_file)
      {
        if ((index + 1) < argc)
          config->file = argv[++index];
        else
          return (false);
      }
    }
    else
      try_parse_file(argv[index], &config->files_head);
    index++;
  }
  return (true);
}
