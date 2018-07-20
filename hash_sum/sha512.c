/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iprokofy <iprokofy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 11:31:15 by Ulliwy            #+#    #+#             */
/*   Updated: 2018/07/20 13:25:20 by iprokofy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <ft_hash.h>
#include <stdio.h>
#include <inttypes.h>

uint64_t	*init_sha512_buffer(void)
{
	uint64_t	*buf;

	buf = (uint64_t *)ft_memalloc(8 * sizeof(uint64_t));
	buf[0] = 0x6a09e667f3bcc908;
	buf[1] = 0xbb67ae8584caa73b;
	buf[2] = 0x3c6ef372fe94f82b;
	buf[3] = 0xa54ff53a5f1d36f1;
	buf[4] = 0x510e527fade682d1;
	buf[5] = 0x9b05688c2b3e6c1f;
	buf[6] = 0x1f83d9abfb41bd6b;
	buf[7] = 0x5be0cd19137e2179;
	return (buf);
}

void		init_words64(uint64_t *words, uint64_t w_arr[80])
{
	int			i;
	uint64_t	s0;
	uint64_t	s1;

	i = 0;
	while (i < 16)
	{
		w_arr[i] = __builtin_bswap64(words[i]);
		i++;
	}
	while (i < 80)
	{
		s0 = right_rotate_64(w_arr[i - 15], 1) ^
				right_rotate_64(w_arr[i - 15], 8) ^ (w_arr[i - 15] >> 7);
		s1 = right_rotate_64(w_arr[i - 2], 19) ^
				right_rotate_64(w_arr[i - 2], 61) ^ (w_arr[i - 2] >> 6);
		w_arr[i] = (w_arr[i - 16] + s0 + w_arr[i - 7] + s1);
		i++;
	}
}

void		process_rounds_512(t_sha512_buf *buf, uint64_t w_arr[80], int i)
{
	uint64_t s0;
	uint64_t maj;
	uint64_t s1;
	uint64_t ch;
	uint64_t temp1;

	while (i < 80)
	{
		s0 = right_rotate_64(buf->a, 28) ^
				right_rotate_64(buf->a, 34) ^ right_rotate_64(buf->a, 39);
		maj = (buf->a & buf->b) ^ (buf->a & buf->c) ^ (buf->b & buf->c);
		s1 = right_rotate_64(buf->e, 14) ^
				right_rotate_64(buf->e, 18) ^ right_rotate_64(buf->e, 41);
		ch = (buf->e & buf->f) ^ ((~(buf->e)) & buf->g);
		temp1 = buf->h + s1 + ch + g_sha512_k[i] + w_arr[i];
		buf->h = buf->g;
		buf->g = buf->f;
		buf->f = buf->e;
		buf->e = buf->d + temp1;
		buf->d = buf->c;
		buf->c = buf->b;
		buf->b = buf->a;
		buf->a = temp1 + s0 + maj;
		i++;
	}
}

void		process_sha512_chunk(unsigned char *chunk, uint64_t *buffer)
{
	uint64_t		*words;
	uint64_t		w_arr[80];
	t_sha512_buf	buf;

	words = (uint64_t *)chunk;
	init_words64(words, w_arr);
	buf.a = buffer[0];
	buf.b = buffer[1];
	buf.c = buffer[2];
	buf.d = buffer[3];
	buf.e = buffer[4];
	buf.f = buffer[5];
	buf.g = buffer[6];
	buf.h = buffer[7];
	process_rounds_512(&buf, w_arr, 0);
	buffer[0] = buffer[0] + buf.a;
	buffer[1] = buffer[1] + buf.b;
	buffer[2] = buffer[2] + buf.c;
	buffer[3] = buffer[3] + buf.d;
	buffer[4] = buffer[4] + buf.e;
	buffer[5] = buffer[5] + buf.f;
	buffer[6] = buffer[6] + buf.g;
	buffer[7] = buffer[7] + buf.h;
}

void		sha512(unsigned char *msg, ssize_t size, t_hash *opts)
{
	uint64_t	*buffer;
	int			i;

	msg = sha512_pad_msg(msg, &size);
	buffer = init_sha512_buffer();
	i = 0;
	while (i < size / 128)
	{
		process_sha512_chunk(msg + i * 128, buffer);
		i++;
	}
	print_hash(buffer, 8, "SHA512", opts);
	free(buffer);
	free(msg);
}
