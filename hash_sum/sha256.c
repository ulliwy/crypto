/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iprokofy <iprokofy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 11:31:15 by Ulliwy            #+#    #+#             */
/*   Updated: 2018/07/20 13:26:24 by iprokofy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <ft_hash.h>

uint32_t	*init_sha256_buffer(void)
{
	uint32_t *buf;

	buf = (uint32_t *)ft_memalloc(8 * sizeof(uint32_t));
	buf[0] = 0x6a09e667;
	buf[1] = 0xbb67ae85;
	buf[2] = 0x3c6ef372;
	buf[3] = 0xa54ff53a;
	buf[4] = 0x510e527f;
	buf[5] = 0x9b05688c;
	buf[6] = 0x1f83d9ab;
	buf[7] = 0x5be0cd19;
	return (buf);
}

void		init_words32(uint32_t *words, uint32_t w_arr[64])
{
	int			i;
	uint32_t	s0;
	uint32_t	s1;

	i = 0;
	while (i < 16)
	{
		w_arr[i] = __builtin_bswap32(words[i]);
		i++;
	}
	while (i < 64)
	{
		s0 = right_rotate(w_arr[i - 15], 7) ^ right_rotate(w_arr[i - 15], 18) ^
				(w_arr[i - 15] >> 3);
		s1 = right_rotate(w_arr[i - 2], 17) ^ right_rotate(w_arr[i - 2], 19) ^
				(w_arr[i - 2] >> 10);
		w_arr[i] = (w_arr[i - 16] + s0 + w_arr[i - 7] + s1);
		i++;
	}
}

void		process_rounds_256(t_sha256_buf *buf, uint32_t w_arr[64], int i)
{
	uint32_t s0;
	uint32_t maj;
	uint32_t s1;
	uint32_t ch;
	uint32_t temp1;

	while (i < 64)
	{
		s0 = right_rotate(buf->a, 2) ^ right_rotate(buf->a, 13) ^
				right_rotate(buf->a, 22);
		maj = (buf->a & buf->b) ^ (buf->a & buf->c) ^ (buf->b & buf->c);
		s1 = right_rotate(buf->e, 6) ^ right_rotate(buf->e, 11) ^
				right_rotate(buf->e, 25);
		ch = (buf->e & buf->f) ^ ((~(buf->e)) & buf->g);
		temp1 = buf->h + s1 + ch + g_sha256_k[i] + w_arr[i];
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

void		process_sha256_chunk(unsigned char *chunk, uint32_t *buffer)
{
	uint32_t		*words;
	uint32_t		w_arr[64];
	t_sha256_buf	buf;

	words = (uint32_t *)chunk;
	init_words32(words, w_arr);
	buf.a = buffer[0];
	buf.b = buffer[1];
	buf.c = buffer[2];
	buf.d = buffer[3];
	buf.e = buffer[4];
	buf.f = buffer[5];
	buf.g = buffer[6];
	buf.h = buffer[7];
	process_rounds_256(&buf, w_arr, 0);
	buffer[0] = buffer[0] + buf.a;
	buffer[1] = buffer[1] + buf.b;
	buffer[2] = buffer[2] + buf.c;
	buffer[3] = buffer[3] + buf.d;
	buffer[4] = buffer[4] + buf.e;
	buffer[5] = buffer[5] + buf.f;
	buffer[6] = buffer[6] + buf.g;
	buffer[7] = buffer[7] + buf.h;
}

void		sha256(unsigned char *msg, ssize_t size, t_hash *opts)
{
	uint32_t	*buffer;
	int			i;

	msg = sha256_pad_msg(msg, &size);
	buffer = init_sha256_buffer();
	i = 0;
	while (i < size / 64)
	{
		process_sha256_chunk(msg + i * 64, buffer);
		i++;
	}
	print_hash(buffer, 8, "SHA256", opts);
	free(buffer);
	free(msg);
}
