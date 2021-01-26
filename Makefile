# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: odhazzar <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/09 07:08:11 by odhazzar          #+#    #+#              #
#    Updated: 2020/06/13 09:27:29 by odhazzar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
FLAGS = -Wall -Werror -Wextra
HEADER = ft_printf.h
SOURCES = \
	ft_printf.c\
	ft_print_utils.c\
	ft_print_hex.c\
	ft_print_number.c\
	ft_print_u.c\
	ft_print_string.c\
	ft_print_conversion.c\
	ft_print_libft.c\
	ft_print_size.c\
	ft_print_float.c\
	ft_print_float_width.c\
	ft_print_exp.c\
	ft_print_g.c
OBJECTS = $(SOURCES:%.c=%.o)

.PHONY: all bonus clean fclean re

all: $(NAME)

$(NAME): $(OBJECTS)
	@ar rc $(NAME) $(OBJECTS)
	@ranlib $(NAME)

%.o: %.c $(HEADER)
	@gcc $(FLAGS) -o $@ -c $<

clean:
	@rm -f $(OBJECTS)

fclean: clean
	@rm -f $(NAME)

re: 
	@$(MAKE) fclean
	@$(MAKE) all

bonus: all