# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iprokofy <iprokofy@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/10/05 13:01:02 by iprokofy          #+#    #+#              #
#    Updated: 2018/04/17 14:35:33 by iprokofy         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ssl
SRC = main.c\
		base64.c\
		buff_read.c\
		des_tables.c\
		des.c\
		print_bits.c\
		block_handle.c\
		put_err.c\
		init.c\
		key_gen.c\
		bit_permut.c\
		des_decode.c\
		des_encode.c\
		\
		md5_prep.c\
		md5_tables.c
FLAGS = -Wall -Wextra -Werror -O3 -flto -march=native -g -fsanitize=address

all: $(NAME)

libft/libft.a:
	$(MAKE) -C libft

ft_ssl: $(SRC) libft/libft.a
	clang $(FLAGS) $(SRC) -Llibft -lft -o $(NAME)

clean:
	rm -f $(SRC:.c=.o)
	rm -f $(LIBFT:.c=.o)
	rm -f -r ft_ssl.dSYM

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C libft fclean

re: fclean all