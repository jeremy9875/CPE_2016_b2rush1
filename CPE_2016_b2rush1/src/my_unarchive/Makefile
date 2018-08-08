##
## Makefile for my_archive in /home/xeo/documents/CPE/CPE_2016_b2rush1/archive
## 
## Made by theo benbezza-grevet
## Login   <theo.benbezza-grevet@epitech.eu>
## 
## Started on  Fri Mar 03 20:55:05 2017 theo benbezza-grevet
## Last update Thu Mar 23 11:20:18 2017 jeremy elkaim
##

CC			= gcc

RM			= rm -rf

CPPFLAGS	= -I include/

CPPFLAGS	+= -I ../../lib/my_compress/include

CFLAGS		= -Wall -Wextra -Werror

LDFLAGS 	= -L ../../lib -lmy_comp

NAME		= my_unarchive

SRCS		= src/program.c \

OBJS		= $(SRCS:.c=.o)


all: libmy_comp $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

libmy_comp:
	@$(MAKE) -C ../../lib/my_compress;

clean:
	$(RM) $(OBJS)
	@$(MAKE) -C ../../lib/my_compress clean;

fclean: clean
	$(RM) $(NAME)
	@$(MAKE) -C ../../lib/my_compress fclean;

re: fclean all

.PHONY: all clean fclean re
