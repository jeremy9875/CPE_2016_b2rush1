/*
** tar_unpack.c for lib_comp in /home/xeo/documents/CPE/CPE_2016_b2rush1/lib/my_compress/src
** 
** Made by theo benbezza-grevet
** Login   <theo.benbezza-grevet@epitech.eu>
** 
** Started on  Sat Mar 04 05:00:20 2017 theo benbezza-grevet
** Last update Sun Mar 05 23:13:26 2017 theo benbezza-grevet
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "tar.h"
#include "path.h"
#include "utilities.h"

static const t_wr_handler	g_handlers[] =
{
  { LF_OLD_NORMAL,	&tar_create_normal },
  { LF_NORMAL,		&tar_create_normal },
  { LF_CONTIG,		&tar_create_normal },
  { LF_LINK,		&tar_create_link },
  { LF_SYMLINK,		&tar_create_symlink },
  { LF_CHR,		&tar_create_chr },
  { LF_BLK,		&tar_create_block },
  { LF_DIR,		&tar_create_dir },
  { LF_FIFO,		&tar_create_fifo }
};

static const t_wr_handler	*get_handler(char identifier)
{
  size_t			idx;
  size_t			len;
  const t_wr_handler		*handler;

  idx = 0;
  len = sizeof(g_handlers) / sizeof(t_wr_handler);
  while (idx < len)
  {
    handler = &g_handlers[idx++];
    if (handler->typeflag == identifier)
      return (handler);
  }
  return (NULL);
}

static bool		unpack_cb(const t_tar *hd, const t_config *config,
				  const uint8_t *data, size_t len)
{
  const t_wr_handler	*handler;

  if (config->extract)
  {
    if (!(handler = get_handler(hd->typeflag)))
      return (false);
    return (handler->func(hd, data, len));
  }
  else
  {
    printf("%s\n", hd->name);
    return (true);
  }
}

bool	tar_unpack_file(const char *file_name, t_config *config)
{
  return (tar_open_file(file_name, &unpack_cb, config));
}
