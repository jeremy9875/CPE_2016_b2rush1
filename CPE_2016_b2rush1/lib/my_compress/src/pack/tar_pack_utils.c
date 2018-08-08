/*
** tar_pack_utils.c for lib_comp in /home/xeo/documents/CPE/CPE_2016_b2rush1/lib/my_compress/src/pack
** 
** Made by theo benbezza-grevet
** Login   <theo.benbezza-grevet@epitech.eu>
** 
** Started on  Sun Mar 05 13:57:23 2017 theo benbezza-grevet
** Last update Fri Mar 17 09:35:37 2017 theo benbezza-grevet
*/

#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <grp.h>
#include <pwd.h>
#include "tar.h"

static const t_stattotype	g_stotps[] =
{
  { S_IFREG, LF_NORMAL },
  { S_IFDIR, LF_DIR },
  { S_IFLNK, LF_LINK },
  { S_IFCHR, LF_CHR },
  { S_IFBLK, LF_BLK },
  { S_IFIFO, LF_FIFO },
};

char		tar_typeflag(const struct stat *statb)
{
  size_t	idx;
  size_t	len;
  char		res;

  idx = 0;
  res = -1;
  len = sizeof(g_stotps) / sizeof(t_stattotype);
  while (idx < len && res == -1)
  {
    if (g_stotps[idx].stat_flag == (statb->st_mode & S_IFMT))
      res = g_stotps[idx].type;
    idx++;
  }
  if (res == LF_LINK && statb->st_nlink == 1)
    res = LF_SYMLINK;
  return (res);
}

bool	set_tar_owner(t_tar *hd, const struct stat *statb)
{
  struct group	*grp;
  struct passwd	*pw;

  if (!(grp = getgrgid(statb->st_gid)) || !(pw = getpwuid(statb->st_uid)))
    return (false);
  sprintf(hd->gid, "%07o", statb->st_gid);
  sprintf(hd->uid, "%07o", statb->st_uid);
  strncpy(hd->gname, grp->gr_name, sizeof(hd->gname));
  strncpy(hd->uname, pw->pw_name, sizeof(hd->uname));
  return (true);
}

bool	set_special(t_tar *hd, const char *file, const struct stat *statb)
{
  if (S_ISBLK(statb->st_mode) || S_ISCHR(statb->st_mode))
  {
    sprintf(hd->devmajor, "%08o", major(statb->st_dev));
    sprintf(hd->devminor, "%08o", minor(statb->st_dev));
  }
  if (S_ISLNK(statb->st_mode))
  {
    if (readlink(file, hd->linkname, sizeof(hd->linkname)) < 0)
      return (false);
  }
  return (true);
}

uint32_t	tar_checksum(t_tar *hd)
{
  uint32_t	checksum;
  uint8_t	*ptr;
  size_t	idx;
  char		*old;

  if (!(old = strdup(hd->chksum)))
    return (0);
  memset(hd->chksum, ' ', sizeof(hd->chksum));
  checksum = 0;
  ptr = (uint8_t*)hd;
  idx = 0;
  while (idx++ < sizeof(t_tar))
    checksum += *ptr++;
  strncpy(hd->chksum, old, strlen(hd->chksum));
  free(old);
  return (checksum);
}
