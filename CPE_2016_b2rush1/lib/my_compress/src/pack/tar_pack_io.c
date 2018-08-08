/*
** tar_pack_io.c for lib_comp in /home/xeo/documents/CPE/CPE_2016_b2rush1/lib/my_compress/src/pack
** 
** Made by theo benbezza-grevet
** Login   <theo.benbezza-grevet@epitech.eu>
** 
** Started on  Sat Mar 04 14:01:21 2017 theo benbezza-grevet
** Last update Sun Mar 05 21:22:28 2017 theo benbezza-grevet
*/

#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include "tar.h"
#include "path.h"

static bool	tar_write_data(FILE *out_file, const char *file_name)
{
  uint8_t	buffer[RECORD_SIZE];
  size_t	res;
  FILE		*in_file;
  bool		state;

  if (!(in_file = fopen(file_name, OPEN_MODE)))
    return (false);
  state = true;
  while (state && (res = fread(buffer, 1, RECORD_SIZE, in_file)) > 0)
  {
    state = fwrite(buffer, 1, res, out_file) == res;
    if (state && res != RECORD_SIZE)
    {
      res = RECORD_SIZE - (res % RECORD_SIZE);
      memset(buffer, 0, res);
      state = (fwrite(buffer, 1, res, out_file) == res);
    }
  }
  return (fclose(in_file) == 0 && state);
}

static bool	tar_add_entry(FILE *file, const char *file_name,
			      const struct stat *statb, const t_config *config)
{
  t_tar		header;

  if (config->verbose)
    printf("%s\n", remove_relat(file_name));
  memset(&header, 0, sizeof(header));
  sprintf(header.mode, "%07o", statb->st_mode & 0777);
  strncpy(header.name, remove_relat(file_name), sizeof(header.name));
  sprintf(header.size, "%011o", (int)statb->st_size);
  sprintf(header.mtime, "%011o", (int)statb->st_mtime);
  strncpy(header.magic, TMAGIC, sizeof(header.magic));
  header.typeflag = tar_typeflag(statb);
  if (!set_tar_owner(&header, statb)|| !set_special(&header, file_name, statb))
    return (false);
  memset(header.chksum, ' ', sizeof(header.chksum));
  sprintf(header.chksum, "%06o", tar_checksum(&header));
  header.chksum[6] = 0;
  if (fwrite(&header, 1, sizeof(header), file) != sizeof(header))
    return (false);
  if (S_ISREG(statb->st_mode))
    return (tar_write_data(file, file_name));
  return (true);
}

static bool	tar_add_dir(FILE *file, const char *dir_name,
			    const char *tar_name, const t_config *config)
{
  DIR		*directory;
  struct dirent	*filei;
  char		*new_path;
  bool		res;

  if (!(directory = opendir(dir_name)))
    return (false);
  res = true;
  while (res && (filei = readdir(directory)) != NULL)
  {
    if (is_useless_path(filei->d_name))
      continue;
    if (!(new_path = combine_path(dir_name, filei->d_name)))
      res = false;
    else
      res = tar_add_path(file, new_path, tar_name, config);
    free(new_path);
  }
  return (closedir(directory) == 0 && res);
}

bool		tar_add_path(FILE *file, const char *path,
			     const char *tar_name, const t_config *config)
{
  struct stat	stat_buffer;

  if (strcmp(remove_relat(tar_name), remove_relat(path)) == 0)
    return (true);
  if (stat(path, &stat_buffer) != 0)
    return (false);
  if (S_ISDIR(stat_buffer.st_mode))
  {
    if (!tar_add_entry(file, path, &stat_buffer, config))
      return (false);
    return (tar_add_dir(file, path, tar_name, config));
  }
  else if (S_ISREG(stat_buffer.st_mode))
    return (tar_add_entry(file, path, &stat_buffer, config));
  else
    return (false);
}
