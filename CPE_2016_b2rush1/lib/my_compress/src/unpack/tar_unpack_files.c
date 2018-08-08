/*
** tar_unpack_files.c for lib_comp in /home/xeo/documents/CPE/CPE_2016_b2rush1/lib/my_compress/src
** 
** Made by theo benbezza-grevet
** Login   <theo.benbezza-grevet@epitech.eu>
** 
** Started on  Sat Mar 04 11:22:31 2017 theo benbezza-grevet
** Last update Sun Mar 05 21:54:56 2017 theo benbezza-grevet
*/

#include <unistd.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>
#include "tar.h"
#include "path.h"

static bool	ensure_dir_exists(const t_tar *hd)
{
  char	dir_name[PATH_MAX + 1];

  if (!strchr(hd->name, DIR_SEPARATOR))
    return (true);
  if (!try_get_dir(dir_name, hd->name))
    return (false);
  if (!create_path(dir_name, DIR_MODE & 0777))
    return (false);
 return (true);
}

bool	tar_create_normal(const t_tar *hd, const uint8_t *data, size_t len)
{
  FILE	*file;

  if (!ensure_dir_exists(hd))
    return (false);
  if (!(file = fopen(hd->name, WRITE_MODE)))
    return (false);
  if (fwrite(data, 1, len, file) != len)
  {
    fclose(file);
    return (false);
  }
  return (fclose(file) == 0);
}

bool	tar_create_link(const t_tar *hd)
{
  if (link(hd->linkname, hd->name) < 0)
    return (false);
  return (true);
}

bool	tar_create_symlink(const t_tar *hd)
{
   if (symlink(hd->linkname, hd->name) < 0)
     return (false);
   return (true);
}
