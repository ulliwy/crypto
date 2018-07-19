/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iprokofy <iprokofy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 11:31:15 by Ulliwy            #+#    #+#             */
/*   Updated: 2018/07/19 13:18:09 by iprokofy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <ft_hash.h>

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

uint32_t		*init_sha256_buffer(void)
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

extern uint32_t	right_rotate(uint32_t x, int c)
{
	return (x >> c) | (x << (32 - c));
}

void			process_sha256_chunk(unsigned char *chunk, uint32_t *buffer)
{
	uint32_t	*words;
	uint32_t	w_arr[64];
	int i;
	uint32_t s0;
	uint32_t s1;
	t_sha256_buf buf;

	words = (uint32_t *)chunk;
	i = 0;
	while (i < 16)
	{
		w_arr[i] = __builtin_bswap32(words[i]);
		i++;
	}
	while (i < 64)
	{
		s0 = right_rotate(w_arr[i - 15], 7) ^ right_rotate(w_arr[i - 15], 18) ^ (w_arr[i - 15] >> 3);
        s1 = right_rotate(w_arr[i - 2], 17) ^ right_rotate(w_arr[i - 2], 19) ^ (w_arr[i - 2] >> 10);
        w_arr[i] = (w_arr[i - 16] + s0 + w_arr[i - 7] + s1);
		i++;
	}
	buf.a = buffer[0];
	buf.b = buffer[1];
	buf.c = buffer[2];
	buf.d = buffer[3];
	buf.e = buffer[4];
	buf.f = buffer[5];
	buf.g = buffer[6];
	buf.h = buffer[7];
	i = 0;
	while (i < 64)
	{
		uint32_t S0 = right_rotate(buf.a, 2) ^ right_rotate(buf.a, 13) ^ right_rotate(buf.a, 22);
		uint32_t maj = (buf.a & buf.b) ^ (buf.a & buf.c) ^ (buf.b & buf.c);
		uint32_t temp2 = S0 + maj;
		uint32_t S1 = right_rotate(buf.e, 6) ^ right_rotate(buf.e, 11) ^ right_rotate(buf.e, 25);
		uint32_t ch = (buf.e & buf.f) ^ ((~(buf.e)) & buf.g);
		uint32_t temp1 = buf.h + S1 + ch + g_sha256_k[i] + w_arr[i];
		buf.h = buf.g;
		buf.g = buf.f;
		buf.f = buf.e;
		buf.e = buf.d + temp1;
		buf.d = buf.c;
		buf.c = buf.b;
		buf.b = buf.a;
		buf.a = temp1 + temp2;
		i++;
	}
	buffer[0] = buffer[0] + buf.a;
	buffer[1] = buffer[1] + buf.b;
	buffer[2] = buffer[2] + buf.c;
	buffer[3] = buffer[3] + buf.d;
	buffer[4] = buffer[4] + buf.e;
	buffer[5] = buffer[5] + buf.f;
	buffer[6] = buffer[6] + buf.g;
	buffer[7] = buffer[7] + buf.h;
}

void			sha256(unsigned char *msg, ssize_t size, t_hash *opts)
{
	uint32_t *buffer;
	int i;

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
