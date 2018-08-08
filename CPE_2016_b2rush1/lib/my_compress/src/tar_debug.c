/*
** tar_debug.c for lib_comp in /home/xeo/documents/CPE/CPE_2016_b2rush1/lib/my_compress/src
** 
** Made by theo benbezza-grevet
** Login   <theo.benbezza-grevet@epitech.eu>
** 
** Started on  Sat Mar 04 02:07:42 2017 theo benbezza-grevet
** Last update Sun Mar 05 18:43:49 2017 theo benbezza-grevet
*/

#include <stdio.h>
#include "utilities.h"
#include "tar.h"

void	tar_header_display(t_tar *hd)
{
  printf("***TAR HEADER***\n");
  printf("Name : %s\n", hd->name);
  printf("Mode : %s\n", hd->mode);
  printf("Uid  : %s\n", hd->uid);
  printf("Gid  : %s\n", hd->gid);
  printf("size : %lu\n", octodec(hd->size));
  printf("mtime: %s\n", hd->mtime);
  printf("chksu: %s\n", hd->chksum);
  printf("tpflg: %c\n", hd->typeflag);
  printf("lnkna: %s\n", hd->linkname);
  printf("magic: %s\n", hd->magic);
  printf("uname: %s\n", hd->uname);
  printf("gname: %s\n", hd->gname);
  printf("devma: %s\n", hd->devmajor);
  printf("devmi: %s\n", hd->devminor);
  printf("\n");
}
