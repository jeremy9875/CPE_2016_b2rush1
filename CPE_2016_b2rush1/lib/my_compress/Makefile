##
## Makefile for my_compress in /home/xeo/documents/CPE/CPE_2016_b2rush1/lib/my_compress
## 
## Made by theo benbezza-grevet
## Login   <theo.benbezza-grevet@epitech.eu>
## 
## Started on  Fri Mar 03 20:48:14 2017 theo benbezza-grevet
## Last update Sun Mar 05 14:48:01 2017 theo benbezza-grevet
##

CC			= gcc

RM			= rm -rf

CFLAGS		+= -Wall -Wextra -Werror -pedantic

CPPFLAGS	+= -I include/

NAME		= libmy_comp.a

SRCS		= src/unpack/tar_unpack.c \
			  src/unpack/tar_unpack_io.c \
			  src/unpack/tar_unpack_files.c \
			  src/unpack/tar_unpack_misc.c \
			  src/pack/tar_pack.c \
			  src/pack/tar_pack_io.c \
			  src/pack/tar_pack_utils.c \
			  src/tar_debug.c \
			  src/path.c \
			  src/utilities.c \
			  src/config.c \

OBJS		= $(SRCS:.c=.o)


all: $(NAME)

$(NAME): $(OBJS)
	ar rc $(NAME) $(OBJS)
	ranlib $(NAME)
	cp $(NAME) ../$(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)
	$(RM) ../$(NAME)

re: fclean all

.PHONY: all clean fclean re
