/*
** tar_unpack_misc.c for lib_comp in /home/xeo/documents/CPE/CPE_2016_b2rush1/lib/my_compress/src
** 
** Made by theo benbezza-grevet
** Login   <theo.benbezza-grevet@epitech.eu>
** 
** Started on  Sat Mar 04 11:23:58 2017 theo benbezza-grevet
** Last update Fri Mar 17 09:47:18 2017 theo benbezza-grevet
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "utilities.h"
#include "path.h"
#include "tar.h"

bool	tar_create_dir(const t_tar *hd)
{
  if (!create_path(hd->name, octodec(hd->mode) & 0777))
    return (false);
  return (true);
}

bool	tar_create_chr(const t_tar *hd)
{
  dev_t	dev;

  dev =  (octodec(hd->devmajor) << 20) | octodec(hd->devminor);
  if (mknod(hd->name, S_IFCHR | (octodec(hd->mode) & 0777), dev) < 0)
    return (false);
  return (true);
}

bool	tar_create_block(const t_tar *hd)
{
  dev_t	dev;

  dev =  (octodec(hd->devmajor) << 20) | octodec(hd->devminor);
  if (mknod(hd->name, S_IFBLK | (octodec(hd->mode) & 0777), dev) < 0)
    return (false);
  return (true);
}

bool	tar_create_fifo(const t_tar *hd)
{
  if (mkfifo(hd->name, octodec(hd->mode) & 0777) < 0)
    return (false);
  return (true);
}
