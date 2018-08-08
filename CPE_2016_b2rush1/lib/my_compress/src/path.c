/*
** path.c for lib_comp in /home/xeo/documents/CPE/CPE_2016_b2rush1/lib/my_compress/src
** 
** Made by theo benbezza-grevet
** Login   <theo.benbezza-grevet@epitech.eu>
** 
** Started on  Sat Mar 04 06:47:28 2017 theo benbezza-grevet
** Last update Fri Mar 17 09:41:38 2017 theo benbezza-grevet
*/

#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <limits.h>
#include "path.h"

bool		create_path(const char *file_path, mode_t mode)
{
  size_t	len;
  char		path[PATH_MAX];
  char		*current;
  char		*end;

  len = strlen(file_path);
  strncpy(path, file_path, len);
  if (path[len - 1] == DIR_SEPARATOR)
    path[len - 1] = 0;
  current = path;
  end = path;
  while (*current)
  {
    if ((end = strchr(end + 1, DIR_SEPARATOR)))
      *end = 0;
    if (mkdir(current, mode) == -1 && errno != EEXIST)
      return (false);
    if (!end)
      break ;
    *end = '/';
  }
  return (true);
}

bool	try_get_dir(char *buffer, const char *file_name)
{
  int	index;

  index = strlen(file_name);
  while (index)
  {
    if (file_name[index] == DIR_SEPARATOR)
    {
      strncpy(buffer, file_name, index);
      buffer[index] = 0;
      return (true);
    }
    index--;
  }
  return (false);
}

char		*combine_path(const char *path, const char *other)
{
  const char	*last_char;
  bool		append_sep;
  char		*res;

  last_char = path;
  while (*last_char && *(last_char + 1))
    last_char++;
  append_sep = (*last_char != DIR_SEPARATOR);
  if (!(res = malloc(strlen(path) + strlen(other) + 1 + append_sep)))
    return (NULL);
  strcpy(res, path);
  if (append_sep)
    strcat(res, "/");
  strcat(res, other);
  return (res);
}

bool	is_useless_path(const char *path)
{
  return (strcmp(path, ".") == 0 || strcmp(path, "..") == 0);
}

const char	*remove_relat(const char *str)
{
  size_t	to_remove;

  if (!str)
    return (NULL);
  if (strncmp(str, "./", 2) == 0)
    to_remove = 2;
  else if (strncmp(str, "../", 3) == 0)
    to_remove = 3;
  else
    to_remove = 0;
  if (to_remove)
    return (remove_relat(str + to_remove));
  else
    return (str);
}
