/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iprokofy <iprokofy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 16:34:08 by Ulliwy            #+#    #+#             */
/*   Updated: 2018/07/19 11:54:31 by iprokofy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_hash.h>
#include <stdlib.h>
#include "libft.h"

void		add_size_representation(unsigned char *msg, ssize_t size,
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

uint32_t	*init_buffer(void)
{
	uint32_t *buf;

	buf = (uint32_t *)malloc(4 * sizeof(uint32_t));
	buf[0] = 0x67452301;
	buf[1] = 0xefcdab89;
	buf[2] = 0x98badcfe;
	buf[3] = 0x10325476;
	return (buf);
}

uint32_t	left_rotate(uint32_t x, int c)
{
	return (x << c) | (x >> (32 - c));
}

void		process_word(int i, uint32_t *f, uint32_t *g, t_md5_buf *buf)
{
	if (i < 16)
	{
		*f = (buf->b & buf->c) | (~(buf->b) & buf->d);
		*g = i;
	}
	else if (i < 32)
	{
		*f = (buf->d & buf->b) | (~(buf->d) & buf->c);
		*g = (5 * i + 1) % 16;
	}
	else if (i < 48)
	{
		*f = buf->b ^ buf->c ^ buf->d;
		*g = (3 * i + 5) % 16;
	}
	else if (i < 64)
	{
		*f = buf->c ^ (buf->b | ~(buf->d));
		*g = (7 * i) % 16;
	}
}

void		update_word_buf(t_md5_buf *buf, int i, uint32_t f)
{
	buf->a = buf->d;
	buf->d = buf->c;
	buf->c = buf->b;
	buf->b = buf->b + left_rotate(f, g_md5_s[i]);
}

void		process_chunk(unsigned char *chunk, uint32_t *buffer)
{
	uint32_t	*words;
	t_md5_buf	buf;
	int			i;
	uint32_t	f;
	uint32_t	g;

	words = (uint32_t *)chunk;
	buf.a = buffer[0];
	buf.b = buffer[1];
	buf.c = buffer[2];
	buf.d = buffer[3];
	i = 0;
	while (i < 64)
	{
		process_word(i, &f, &g, &buf);
		f = f + buf.a + g_md5_k[i] + words[g];
		update_word_buf(&buf, i, f);
		i++;
	}
	buffer[0] = buffer[0] + buf.a;
	buffer[1] = buffer[1] + buf.b;
	buffer[2] = buffer[2] + buf.c;
	buffer[3] = buffer[3] + buf.d;
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

void	md5(unsigned char *msg, ssize_t size, t_hash *opts)
{
	int			i;
	uint32_t	*buffer;

	msg = md5_pad_msg(msg, &size);
	buffer = init_buffer();
	i = 0;
	while (i < size / 64)
	{
		process_chunk(msg + i * 64, buffer);
		i++;
	}
	i = 0;
	while (i < 4)
	{
		buffer[i] = __builtin_bswap32(buffer[i]);
		i++;
	}
	print_hash(buffer, 4, "MD5", opts);
	free(buffer);
}
