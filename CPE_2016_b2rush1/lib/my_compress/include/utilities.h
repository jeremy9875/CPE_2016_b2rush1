/*
** utilities.h for  in /home/xeo/documents/CPE/CPE_2016_b2rush1/lib/my_compress/include
** 
** Made by theo benbezza-grevet
** Login   <theo.benbezza-grevet@epitech.eu>
** 
** Started on  Sat Mar 04 02:53:57 2017 theo benbezza-grevet
** Last update Sat Mar 04 17:43:36 2017 theo benbezza-grevet
*/

#ifndef UTILITES_H
# define UTILITES_H

# include <stdint.h>
# include <stddef.h>
# include <stdbool.h>

uint64_t	octodec(const char *str);
bool		is_all_zero(void *ptr, size_t len);

# define MY_EXIT_ERROR		(84)
# define MY_EXIT_SUCCESS	(0)

#endif /* !UTILITES_H */
