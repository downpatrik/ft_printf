# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wvenita <wvenita@student.21-school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/03 22:27:50 by wvenita           #+#    #+#              #
#    Updated: 2020/02/06 15:51:03 by wvenita          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

C = clang

NAME = libft.a

FLAGS = -Wall -Wextra -Werror -O2

HEADER = libft.h

LIBFILES = $(SRC:.c=.o)

SRC = ft_atoi.c \
	  ft_bzero.c \
	  ft_memchr.c \
	  ft_memcpy.c \
	  ft_memset.c \
	  ft_dpow.c \
	  ft_strchr.c \
	  ft_strchri.c \
	  ft_strlen.c \
	  ft_strncmp.c \
	  ft_wcharlen.c \
	  ft_wstrlen.c \
		ft_isdigit.c \
		ft_isspace.c

all: $(NAME)

$(NAME):
	@gcc $(FLAGS) -c $(SRC) -I $(HEADER)
	@ar rc $(NAME) $(LIBFILES)
	@ranlib $(NAME)

clean:
	@rm -f $(LIBFILES)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
