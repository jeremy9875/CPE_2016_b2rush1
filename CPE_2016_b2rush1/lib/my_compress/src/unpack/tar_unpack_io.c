/*
** tar_unpack_io.c for lib_comp in /home/xeo/documents/CPE/CPE_2016_b2rush1/lib/my_compress/src
** 
** Made by theo benbezza-grevet
** Login   <theo.benbezza-grevet@epitech.eu>
** 
** Started on  Fri Mar 03 23:35:16 2017 theo benbezza-grevet
** Last update Sun Mar 05 22:06:05 2017 theo benbezza-grevet
*/

#include <stdio.h>
#include <sys/stat.h>
#include "tar.h"
#include "utilities.h"

static bool	get_file_content(FILE *file, const t_tar *tar,
				 uint8_t **data, size_t *size)
{
  size_t	res;

  *size = octodec(tar->size);
  if (tar->typeflag != LF_NORMAL && tar->typeflag != LF_OLD_NORMAL)
  {
    *data = NULL;
    *size = 0;
    return (true);
  }
  if (!(*data = malloc(sizeof(uint8_t) * *size)))
    return (false);
  if ((res = fread(*data, 1, *size, file)) != *size)
    return (false);
  if (fseek(file, (RECORD_SIZE - (*size % RECORD_SIZE)), SEEK_CUR) != 0)
    return (false);
  return (true);
}

static bool	parse_file(FILE *file, t_tar_cb cb, void *ctx)
{
  t_tar		header;
  int		res;
  uint8_t	*data;
  size_t	size;

  while ((res = fread(&header, 1, sizeof(header), file)) == sizeof(header))
  {
    if (is_all_zero(&header, sizeof(header)))
      continue ;
    if (!get_file_content(file, &header, &data, &size))
      return (false);
    if (!cb(&header, ctx, data, size))
      return (false);
  }
  return (true);
}

bool	tar_open_file(const char *file_name, t_tar_cb cb, void *ctx)
{
  FILE	*file;

  if (!(file = fopen(file_name, OPEN_MODE)))
    return (false);
  if (!parse_file(file, cb, ctx))
  {
    fclose(file);
    return (false);
  }
  return (fclose(file) == 0);
}
