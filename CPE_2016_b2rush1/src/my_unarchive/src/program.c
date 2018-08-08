/*
** program.c for my_unarchive in /home/xeo/documents/CPE/CPE_2016_b2rush1/my_unarchive/src
** 
** Made by theo benbezza-grevet
** Login   <theo.benbezza-grevet@epitech.eu>
** 
** Started on  Sat Mar 04 15:02:41 2017 theo benbezza-grevet
** Last update Fri Mar 17 09:34:47 2017 theo benbezza-grevet
*/

#include "unarchive.h"
#include "utilities.h"
#include "tar.h"

int		main(int ac, char **av)
{
  t_config	config;

  if (ac != 2)
  {
    fprintf(stderr, USAGE_FMT);
    return (MY_EXIT_ERROR);
  }
  init_config(&config);
  config.extract = true;
  if (!tar_unpack_file(av[1], &config))
  {
    fprintf(stderr, ERROR_FMT, av[1]);
    return (MY_EXIT_ERROR);
  }
  return (MY_EXIT_SUCCESS);
}
