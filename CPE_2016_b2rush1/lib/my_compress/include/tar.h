/*
** tar.h for /home/xeo/documents/CPE/CPE_2016_b2rush1/lib/my_compress/include/tar.h in /home/xeo/documents/CPE/CPE_2016_b2rush1/lib/my_compress/include
** 
** Made by theo benbezza-grevet
** Login   <theo.benbezza-grevet@epitech.eu>
** 
** Started on  Fri Mar 03 23:01:59 2017 theo benbezza-grevet
** Last update Sun Mar 05 23:00:38 2017 theo benbezza-grevet
*/

#ifndef TAR_H_
# define TAR_H_

# include <stdint.h>
# include <stdbool.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/stat.h>

# define RECORD_SIZE	(512)
# define NAME_SIZE	(100)
# define TUNM_LEN	(32)
# define TGNM_LEN	(32)

typedef struct	s_tar
{
  char		name[NAME_SIZE];
  char		mode[8];
  char		uid[8];
  char		gid[8];
  char		size[12];
  char		mtime[12];
  char		chksum[8];
  char		typeflag;
  char		linkname[NAME_SIZE];
  char		magic[8];
  char		uname[TUNM_LEN];
  char		gname[TGNM_LEN];
  char		devmajor[8];
  char		devminor[8];
  char		padding[167];
}		t_tar;

# define TMAGIC		("ustar  ")

# define LF_OLD_NORMAL	(0)
# define LF_NORMAL	('0')
# define LF_LINK	('1')
# define LF_SYMLINK	('2')
# define LF_CHR		('3')
# define LF_BLK		('4')
# define LF_DIR		('5')
# define LF_FIFO	('6')
# define LF_CONTIG	('7')

# define TSUID		(04000)
# define TSGID		(02000)
# define TSVTX		(01000)

# define TUREAD		(00400)
# define TUWRITE	(00200)
# define TUEXEC		(00100)
# define TGREAD		(00040)
# define TGWRITE	(00020)
# define TGEXEC		(00010)
# define TOREAD		(00004)
# define TOWRITE	(00002)
# define TOEXEC		(00001)

# define OPEN_MODE	("rb")
# define WRITE_MODE	("wb")
# define DIR_MODE	(0755)
# define END_PADD_LEN	(2 * RECORD_SIZE)

typedef bool	(*t_tar_cb)();

typedef struct	s_config
{
  bool		verbose;
  const char	*tar_name;
  bool		extract;
}		t_config;

void		init_config(t_config *config);

bool		tar_open_file(const char *file_name, t_tar_cb cb, void *ctx);
bool		tar_add_path(FILE *file, const char *file_name,
			     const char *tar_name, const t_config *config);

bool		tar_unpack_file(const char *file_name, t_config *config);
bool		tar_pack_paths(const char *file_name, const t_config *config,
			       const char **paths, size_t len);

void		tar_header_display(t_tar *tar_header);
void		tar_destroy(t_tar *tar_header);

typedef bool	(*t_cr_func)();
typedef struct	s_wr_handler
{
  char		typeflag;
  t_cr_func	func;
}		t_wr_handler;

bool		tar_create_normal(const t_tar *hd,
				  const uint8_t *data, size_t len);
bool		tar_create_dir(const t_tar *hd);
bool		tar_create_link(const t_tar *hd);
bool		tar_create_symlink(const t_tar *hd);
bool		tar_create_chr(const t_tar *hd);
bool		tar_create_block(const t_tar *hd);
bool		tar_create_fifo(const t_tar *hd);


bool		set_tar_owner(t_tar *hd, const struct stat *statb);
bool		set_special(t_tar *hd,
			    const char *file, const struct stat *statb);
uint32_t	tar_checksum(t_tar *hd);

typedef struct	s_stattotype
{
  uint32_t	stat_flag;
  char		type;
}		t_stattotype;
char		tar_typeflag(const struct stat *statb);

#endif /* !TAR_H_ */
