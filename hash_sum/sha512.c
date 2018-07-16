/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ulliwy <Ulliwy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 11:31:15 by Ulliwy            #+#    #+#             */
/*   Updated: 2018/07/16 16:47:51 by Ulliwy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <ft_hash.h>
#include <stdio.h>
#include <inttypes.h>

unsigned char *sha512_pad_msg(unsigned char *msg, ssize_t *size)
{
	ssize_t bit_size;
	ssize_t new_size;
	unsigned char *new_msg;

	bit_size = (*size) * 8;
	new_size = ((bit_size + 128) / 1024) * 1024 + 1024;
	new_msg = (unsigned char *)ft_memalloc(new_size / 8);
	ft_memcpy(new_msg, msg, (size_t)*size);
	new_msg[*size] = 128;
	add_big_endian_size(new_msg, *size * 8, new_size);
	*size = new_size / 8;
	return (new_msg);
}

uint64_t *init_sha512_buffer()
{
	uint64_t *buf;

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

extern uint64_t right_rotate_64(uint64_t x, int c)
{
	return (x >> c) | (x << (64 - c));
}

void 	process_sha512_chunk(unsigned char *chunk, uint64_t *buffer)
{
	uint64_t *words;
	uint64_t w_arr[80];
	int i;
	uint64_t s0;
	uint64_t s1;
	t_sha512_buf buf;

	words = (uint64_t *)chunk;
	i = 0;
	while (i < 64)
	{
		w_arr[i] = 0;
		i++;
	}
	i = 0;
	while (i < 16)
	{
		w_arr[i] = __builtin_bswap64(words[i]);
		i++;
	}
	
	while (i < 80)
	{
		s0 = right_rotate_64(w_arr[i - 15], 1) ^ right_rotate_64(w_arr[i - 15], 8) ^ (w_arr[i - 15] >> 7);
        s1 = right_rotate_64(w_arr[i - 2], 19) ^ right_rotate_64(w_arr[i - 2], 61) ^ (w_arr[i - 2] >> 6);
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
	while (i < 80)
	{
		uint64_t S0 = right_rotate_64(buf.a, 28) ^ right_rotate_64(buf.a, 34) ^ right_rotate_64(buf.a, 39);
		uint64_t maj = (buf.a & buf.b) ^ (buf.a & buf.c) ^ (buf.b & buf.c);
		uint64_t temp2 = S0 + maj;
		uint64_t S1 = right_rotate_64(buf.e, 14) ^ right_rotate_64(buf.e, 18) ^ right_rotate_64(buf.e, 41);
		uint64_t ch = (buf.e & buf.f) ^ ((~(buf.e)) & buf.g);
        uint64_t temp1 = buf.h + S1 + ch + g_sha512_k[i] + w_arr[i];
        
        buf.h = buf.g;
        buf.g = buf.f;
        buf.f = buf.e;
        buf.e = buf.d + temp1;
        buf.d = buf.c;
        buf.c = buf.b;
        buf.b = buf.a;
        buf.a = temp1 + temp2;

        // printf("%d %" PRIx64 " %" PRIx64 " %" PRIx64 " %" PRIx64 
        // 	" %" PRIx64 " %" PRIx64 " %" PRIx64 " %" PRIx64 "\n",
        // 	i, buf.a, buf.b, buf.c, buf.d, buf.e, buf.f, buf.g, buf.h);
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

	printf("%" PRIx64 " %" PRIx64 " %" PRIx64 " %" PRIx64 
        	" %" PRIx64 " %" PRIx64 " %" PRIx64 " %" PRIx64 "\n",
        	buffer[0], buffer[1], buffer[2], buffer[3], buffer[4], buffer[5], buffer[6], buffer[7]);
}

void	sha512(unsigned char *msg, ssize_t size, t_hash *opts)
{
	uint64_t *buffer;
	int i;

	msg = sha512_pad_msg(msg, &size);
	buffer = init_sha512_buffer();
	// for (int i = 0; i < size; i++)
	// {
	// 	if (i && i % 8 == 0)
	// 		printf(" ");
	// 	if (i && i % 32 == 0)
	// 		printf("\n");

	// 	printf("%02x", msg[i]);
	// }
	// printf("\n");

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