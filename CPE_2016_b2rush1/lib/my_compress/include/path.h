/*
** path.h for lib_comp in /home/xeo/documents/CPE/CPE_2016_b2rush1/lib/my_compress/include
** 
** Made by theo benbezza-grevet
** Login   <theo.benbezza-grevet@epitech.eu>
** 
** Started on  Sat Mar 04 06:45:21 2017 theo benbezza-grevet
** Last update Fri Mar 17 09:39:06 2017 theo benbezza-grevet
*/

#ifndef PATH_H_
# define PATH_H_

# include <stdbool.h>
# include <sys/stat.h>

# define DIR_SEPARATOR	('/')

bool		create_path(const char *file_path, mode_t mode);
bool		try_get_dir(char *buffer, const char *file_name);
char		*combine_path(const char *path, const char *other);
bool		is_useless_path(const char *path);
const char	*remove_relat(const char *str);

#endif /* !PATH_H_ */
