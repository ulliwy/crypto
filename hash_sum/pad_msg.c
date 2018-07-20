/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pad_msg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iprokofy <iprokofy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/20 13:14:08 by iprokofy          #+#    #+#             */
/*   Updated: 2018/07/20 13:25:37 by iprokofy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_hash.h"
#include "libft.h"

void			add_big_endian_size(unsigned char *msg, ssize_t size,
									ssize_t new_size)
{
	msg[new_size / 8 - 8] = (char)(size >> (8 * 7));
	msg[new_size / 8 - 7] = (char)(size >> (8 * 6));
	msg[new_size / 8 - 6] = (char)(size >> (8 * 5));
	msg[new_size / 8 - 5] = (char)(size >> (8 * 4));
	msg[new_size / 8 - 4] = (char)(size >> (8 * 3));
	msg[new_size / 8 - 3] = (char)(size >> (8 * 2));
	msg[new_size / 8 - 2] = (char)(size >> (8 * 1));
	msg[new_size / 8 - 1] = (char)(size >> (8 * 0));
}

void			add_size_representation(unsigned char *msg, ssize_t size,
									ssize_t new_size)
{
	msg[new_size / 8 - 1] = (char)(size >> (8 * 7));
	msg[new_size / 8 - 2] = (char)(size >> (8 * 6));
	msg[new_size / 8 - 3] = (char)(size >> (8 * 5));
	msg[new_size / 8 - 4] = (char)(size >> (8 * 4));
	msg[new_size / 8 - 5] = (char)(size >> (8 * 3));
	msg[new_size / 8 - 6] = (char)(size >> (8 * 2));
	msg[new_size / 8 - 7] = (char)(size >> (8 * 1));
	msg[new_size / 8 - 8] = (char)(size >> (8 * 0));
}

unsigned char	*sha512_pad_msg(unsigned char *msg, ssize_t *size)
{
	ssize_t			bit_size;
	ssize_t			new_size;
	unsigned char	*new_msg;

	bit_size = (*size) * 8;
	new_size = ((bit_size + 128) / 1024) * 1024 + 1024;
	new_msg = (unsigned char *)ft_memalloc(new_size / 8);
	ft_memcpy(new_msg, msg, (size_t)*size);
	new_msg[*size] = 128;
	add_big_endian_size(new_msg, *size * 8, new_size);
	*size = new_size / 8;
	return (new_msg);
}

unsigned char	*sha256_pad_msg(unsigned char *msg, ssize_t *size)
{
	ssize_t			bit_size;
	ssize_t			new_size;
	unsigned char	*new_msg;

	bit_size = (*size) * 8;
	new_size = ((bit_size + 64) / 512) * 512 + 448 + 64;
	new_msg = (unsigned char *)ft_memalloc(new_size / 8 + 8);
	ft_memcpy(new_msg, msg, (size_t)*size);
	new_msg[*size] = 128;
	add_big_endian_size(new_msg, *size * 8, new_size);
	*size = new_size / 8;
	return (new_msg);
}

unsigned char	*md5_pad_msg(unsigned char *msg, ssize_t *size)
{
	ssize_t			bit_size;
	ssize_t			new_size;
	unsigned char	*new_msg;

	bit_size = (*size) * 8;
	new_size = ((bit_size + 64) / 512) * 512 + 448 + 8 * 8;
	new_msg = (unsigned char *)ft_memalloc(new_size / 8 + 8);
	ft_memcpy(new_msg, msg, (size_t)*size);
	new_msg[*size] = 128;
	add_size_representation(new_msg, *size * 8, new_size);
	*size = new_size / 8;
	return (new_msg);
}
