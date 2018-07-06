/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ulliwy <Ulliwy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 11:31:15 by Ulliwy            #+#    #+#             */
/*   Updated: 2018/07/06 16:33:16 by Ulliwy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_hash.h"
#include <stdio.h>

void add_big_endian_size(unsigned char *msg, ssize_t size, ssize_t new_size)
{
	//printf("repr: %zu\n", size);
	msg[new_size / 8 - 8] = (char)(size >> (8 * 7));
	msg[new_size / 8 - 7] = (char)(size >> (8 * 6));
	msg[new_size / 8 - 6] = (char)(size >> (8 * 5));
	msg[new_size / 8 - 5] = (char)(size >> (8 * 4));
	msg[new_size / 8 - 4] = (char)(size >> (8 * 3));
	msg[new_size / 8 - 3] = (char)(size >> (8 * 2));
	msg[new_size / 8 - 2] = (char)(size >> (8 * 1));
	msg[new_size / 8 - 1] = (char)(size >> (8 * 0));
}

unsigned char *sha256_pad_msg(unsigned char *msg, ssize_t *size)
{
	ssize_t bit_size;
	ssize_t new_size;
	unsigned char *new_msg;

	bit_size = (*size) * 8;
	new_size = ((bit_size + 64) / 512) * 512 + 448 + 64; // in bits
	new_msg = (unsigned char *)ft_memalloc(new_size / 8 + 8);
	ft_memcpy(new_msg, msg, (size_t)*size);
	new_msg[*size] = 128;
	//printf("%lu %lu\n", *size, new_size);
	add_big_endian_size(new_msg, *size * 8, new_size);
	*size = new_size / 8;
	//free(msg);
	return (new_msg);
}

void	sha256(unsigned char *msg, ssize_t size, t_hash *opts)
{
	// for (int i = 0; i < size; i++)
	// {
	// 	// if (i != 0 && i % 64 == 0)
	// 	//  	printf("\n");
	// 	// if (i != 0 && i % 8 == 0)
	// 	//  	printf("\n");
	// 	printf("%d %d\n", i, msg[i]);
	// 	// print_bits(msg[i], 8);
	// 	// write(1, " ", 1);
	// }
	printf("%zu\n", size);
	msg = sha256_pad_msg(msg, &size);
	//printf("size: %lu", size);
	for (int i = 0; i < size; i++)
	{
		if (i != 0 && i % 64 == 0)
			write(1, "\n", 1);
		if (i != 0 && i % 8 == 0)
			write(1, "\n", 1);
		print_bits(msg[i], 8);
		write(1, " ", 1);
	}
	write(1, "\n", 1);
	// for (int i = 0; i < size; i++)
	// {
	// 	// if (i != 0 && i % 64 == 0)
	// 	//  	printf("\n");
	// 	// if (i != 0 && i % 8 == 0)
	// 	//  	printf("\n");
	// 	printf("%d %d\n", i, msg[i]);
	// 	// print_bits(msg[i], 8);
	// 	// write(1, " ", 1);
	// }
	//msg = NULL;
	//size = 0;
	opts = NULL;
	//printf("SHA!!!\n");
}