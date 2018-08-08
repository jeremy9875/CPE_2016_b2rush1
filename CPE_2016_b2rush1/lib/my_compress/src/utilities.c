/*
** utilities.c for my_comp in /home/xeo/documents/CPE/CPE_2016_b2rush1/lib/my_compress/src
** 
** Made by theo benbezza-grevet
** Login   <theo.benbezza-grevet@epitech.eu>
** 
** Started on  Sat Mar 04 02:53:46 2017 theo benbezza-grevet
** Last update Fri Mar 17 09:42:59 2017 theo benbezza-grevet
*/

#include <stdio.h>
#include <string.h>
#include "utilities.h"

uint64_t	 octodec(const char *str)
{
  size_t	i;
  uint64_t	decimal;
  uint64_t	weight;
  size_t	size;

  decimal = 0;
  weight = 1;
  i = 0;
  size = strlen(str);
  while (*str == '0')
  {
    size--;
    str++;
  }
  if (*str == 0)
    return (0);
  str += size - 1;
  while (i++ < size)
  {
    decimal += weight * (*str - '0');
    weight *= 8;
    str--;
  }
  return (decimal);
}

bool		is_all_zero(void *ptr, size_t len)
{
  uint8_t	*data;

  data = ptr;
  while (len--)
  {
    if (*data != 0)
      return (false);
    data++;
  }
  return (true);
}
