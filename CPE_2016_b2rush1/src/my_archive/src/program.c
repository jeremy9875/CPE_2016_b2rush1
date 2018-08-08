/*
** program.c for my_archive in /home/xeo/documents/CPE/CPE_2016_b2rush1/my_archive/src
** 
** Made by theo benbezza-grevet
** Login   <theo.benbezza-grevet@epitech.eu>
** 
** Started on  Sat Mar 04 15:02:01 2017 theo benbezza-grevet
** Last update Sun Mar 05 23:00:10 2017 theo benbezza-grevet
*/

#include "tar.h"
#include "utilities.h"
#include "archive.h"

int		main(int ac, char **av)
{
  t_config	config;

  if (ac < 3)
  {
    fprintf(stderr, USAGE_FMT);
    return (MY_EXIT_ERROR);
  }
  init_config(&config);
  if (!tar_pack_paths(av[1], &config, (const char **)&av[2], (ac - 2)))
  {
    fprintf(stderr, ERROR_FMT, av[1]);
    return (MY_EXIT_ERROR);
  }
  return (MY_EXIT_SUCCESS);
}
