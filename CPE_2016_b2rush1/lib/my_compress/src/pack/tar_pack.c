/*
** tar_pack.c for lib_comp in /home/xeo/documents/CPE/CPE_2016_b2rush1/lib/my_compress/src/pack
** 
** Made by theo benbezza-grevet
** Login   <theo.benbezza-grevet@epitech.eu>
** 
** Started on  Sat Mar 04 14:22:28 2017 theo benbezza-grevet
** Last update Sun Mar 05 22:06:09 2017 theo benbezza-grevet
*/

#include <stdio.h>
#include <string.h>
#include "tar.h"

static bool	add_end_padd(FILE *file)
{
  char		data[RECORD_SIZE];
  size_t	idx;
  size_t	res;

  memset(data, 0, RECORD_SIZE);
  idx = 0;
  while (idx < END_PADD_LEN)
  {
    if ((res = fwrite(data, 1, RECORD_SIZE, file)) != RECORD_SIZE)
      return (false);
    idx += res;
  }
  return (true);
}

bool	tar_pack_paths(const char *file_name, const t_config *config,
		       const char **paths, size_t len)
{
  FILE	*file;
  bool	result;

  if (!(file = fopen(file_name, WRITE_MODE)))
    return (false);
  result = true;
  while (result && len--)
    result = tar_add_path(file, *paths++, file_name, config);
  if (result)
    result = add_end_padd(file);
  return (fclose(file) == 0 && result);
}
