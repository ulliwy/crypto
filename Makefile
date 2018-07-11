# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: Ulliwy <Ulliwy@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/10/05 13:01:02 by iprokofy          #+#    #+#              #
#    Updated: 2018/07/10 17:01:10 by Ulliwy           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ssl
SRC = main.c\
		init.c\
		buff_read.c\
		print_bits.c\
		put_err.c\
		\
		b64/base64.c\
		\
		des/des_tables.c\
		des/des.c\
		des/block_handle.c\
		des/key_gen.c\
		des/bit_permut.c\
		des/des_decode.c\
		des/des_encode.c\
		\
		hash_sum/prep_hash.c\
		hash_sum/hash_tables.c\
		hash_sum/sha256.c\
		hash_sum/md5.c\
		hash_sum/print_hash.c
FLAGS = -Wall -Wextra -Werror -O3 -flto -march=native

all: $(NAME)

libft/libft.a:
	$(MAKE) -C libft

ft_ssl: $(SRC) libft/libft.a
	clang $(FLAGS) $(SRC) -Llibft -lft -Iincludes -Ilibft -o $(NAME)

clean:
	rm -f $(SRC:.c=.o)
	$(MAKE) -C libft clean
	rm -f -r ft_ssl.dSYM

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C libft fclean

re: fclean all