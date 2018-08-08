/*
** program.c for my_tar in /home/xeo/documents/CPE/CPE_2016_b2rush1/my_tar/src
** 
** Made by theo benbezza-grevet
** Login   <theo.benbezza-grevet@epitech.eu>
** 
** Started on  Sat Mar 04 01:30:34 2017 theo benbezza-grevet
** Last update Sun Mar 05 23:32:22 2017 theo benbezza-grevet
*/

#include "tar.h"
#include "my_tar.h"
#include "arg_parser.h"
#include "utilities.h"

static bool	check_args(const t_arguments *config)
{
  int		op;

  op = config->options;
  if (!(op & op_create) && !(op & op_extract) && !(op & op_list))
    return (false);
  if ((op & op_create) && ((op & op_extract) || (op & op_list)))
    return (false);
  if ((op & op_extract) && ((op & op_create) || (op & op_list)))
    return (false);
  if ((op & op_list) && ((op & op_create) || (op & op_extract)))
    return (false);
  if (!(config->options & op_file))
    return (false);
  if (!config->file)
    return (false);
  return (true);
}

static bool	tar_dat_internal(const t_config *tar_config,
				 const t_arguments *args)
{
  char		**lst;
  const t_node	*current;
  size_t	lst_size;

  if (!(lst = malloc(sizeof(char *) * collection_size(args->files_head))))
    return (false);
  current = args->files_head;
  lst_size = 0;
  while (current)
  {
    lst[lst_size++] = current->data;
    current = current->next;
  }
  if (!tar_pack_paths(args->file, tar_config, (const char **)lst, lst_size))
  {
    free(lst);
    fprintf(stderr, ERROR_FMT);
    return (false);
  }
  free(lst);
  return (true);
}

static bool	process(const t_arguments *config)
{
  t_config	tar_config;

  if (config->options & op_extract)
  {
    tar_config.extract = true;
    return (tar_unpack_file(config->file, &tar_config));
  }
  else if (config->options & op_create)
    return (tar_dat_internal(&tar_config, config));
  else if (config->options & op_list)
  {
    tar_config.extract = false;
    return (tar_unpack_file(config->file, &tar_config));
  }
  return (false);
}

int		main(int ac, char **av)
{
  t_arguments	config;

  config.options = 0;
  config.files_head = NULL;
  config.file = NULL;
  if (!try_parse_args(ac, av, &config))
  {
    fprintf(stderr, ERROR_STR);
    return (MY_EXIT_ERROR);
  }
  if (!check_args(&config))
  {
    fprintf(stderr, ARGS_ERR);
    return (MY_EXIT_ERROR);
  }
  if (!process(&config))
  {
    fprintf(stderr, PROCESS_ERR);
    return (MY_EXIT_ERROR);
  }
  return (MY_EXIT_SUCCESS);
}
