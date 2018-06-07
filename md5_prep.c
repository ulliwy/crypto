/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_prep.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iprokofy <iprokofy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 14:34:02 by iprokofy          #+#    #+#             */
/*   Updated: 2018/04/20 14:46:43 by iprokofy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int		md5_err_usage()
{
	ft_putstr("usage: ft_ssl md5 [-pqr] [-s string] [files ...]\n");
	return (1);
}

int		md5_err_options(char opt)
{
	ft_putstr("ft_ssl md5: illegal option -- ");
	ft_putchar(opt);
	ft_putstr("\n");
	return (0);
}

void add_size_representation(unsigned char *msg, ssize_t size, ssize_t new_size)
{
	msg[new_size / 8] = (char)(size >> (8 * 3));
	msg[new_size / 8 + 1] = (char)(size >> (8 * 2));
	msg[new_size / 8 + 2] = (char)(size >> 8);
	msg[new_size / 8 + 3] = (char)size;
	msg[new_size / 8 + 4] = (char)(size >> (8 * 7));
	msg[new_size / 8 + 5] = (char)(size >> (8 * 6));
	msg[new_size / 8 + 6] = (char)(size >> (8 * 5));
	msg[new_size / 8 + 7] = (char)(size >> (8 * 4));
}

unsigned char *pad_msg(unsigned char *msg, ssize_t *size)
{
	ssize_t bit_size;
	ssize_t new_size;
	unsigned char *new_msg;

	bit_size = (*size) * 8;
	new_size = ((bit_size + 64) / 512) * 512 + 448;
	new_msg = (unsigned char *)ft_memalloc(new_size / 8 + 8);
	ft_strcpy((char *)new_msg, (char *)msg);
	new_msg[*size] = 128;
	add_size_representation(new_msg, *size, new_size);
	*size = new_size;
	//free(msg);
	return (new_msg);
}

uint32_t *init_buffer()
{
	uint32_t *buf;

	buf = (uint32_t *)malloc(4 * sizeof(uint32_t));
	buf[0] = 0x67452301;
	buf[1] = 0xefcdab89;
	buf[2] = 0x98badcfe;
	buf[3] = 0x10325476;
	return (buf);
}

uint32_t left_rotate(uint32_t x, int c)
{
	return (x << c) | (x >> (32 - c));
}

void	proceed_word(uint32_t *words, t_md5_buf *buf)
{
	int i;
	uint32_t F;
	uint32_t g;

	i = 0;
	while (i < 64)
	{
		if (i < 16)
		{
			F = (buf->b & buf->c) | (~(buf->b) & buf->d);
			g = i;
		}
		else if (i < 32)
		{
			F = (buf->d & buf->b) | (~(buf->d) & buf->c);
			g = (5 * i + 1) % 16;
		}
		else if (i < 48)
		{
			F = buf->b ^ buf->c ^ buf->d;
			g = (3 * i + 5) % 16;
		}
		else if (i < 64)
		{
			F = buf->c ^ (buf->b | ~(buf->d));
			g = (7 * i) % 16;
		}
		F = F + buf->a + g_md5_K[i] + words[g];
		buf->a = buf->d;
		buf->d = buf->c;
		buf->c = buf->b;
		buf->b = buf->b + left_rotate(F, g_md5_s[i]);
		i++;
	}
}

void	proceed_chunk(unsigned char *chunk, uint32_t *buffer)
{
	uint32_t *words;
	t_md5_buf cur_buf;
	int i;

	cur_buf.a = buffer[0];
	cur_buf.b = buffer[1];
	cur_buf.c = buffer[2];
	cur_buf.d = buffer[3];

	words = (uint32_t *)chunk;
	i = 0;
	while (i < 16)
	{
		proceed_word(words, &cur_buf);
		buffer[0] = buffer[0] + cur_buf.a;
		buffer[1] = buffer[1] + cur_buf.b;
		buffer[2] = buffer[2] + cur_buf.c;
		buffer[3] = buffer[3] + cur_buf.d;
		i++;
	}
}

void	md5(unsigned char *msg, ssize_t size)
{
	int i;
	uint32_t *buffer;

	msg = pad_msg(msg, &size);
	buffer = init_buffer();

	i = 0;
	while (i < size / 512)
	{
		proceed_chunk(msg + i * 512, buffer);
		i++;
	}
	printf("%x %x %x %x\n", buffer[0], buffer[1],buffer[2], buffer[3]);
	free(msg);
	free(buffer);
	// unsigned long bit_size;
	// int new_size;
	// unsigned char *new;
	// int i;
	// int k;

	// new = (unsigned char*)msg;
	// bit_size = size * 8;
	// new_size = ((bit_size + 64) / 512) * 512 + 448;

	// printf("%lu %lu %d\n", size, bit_size, new_size);
	// //print_bits_long(bit_size, 8);
	
	// // padding
	// if (opts->s)
	// {
	// 	new = (unsigned char*)ft_memalloc(new_size / 8 + 8);
	// 	ft_strcpy((char*)new, msg);
	// }

	// // add '1' bit and pad by '0's
	// new[size] = 128;
	// print_bits_long(size, 8);
	// ft_putstr("\n\n");

	// // adding 64-bit size representation. low-ordered 4 bytes first
	// new[new_size / 8] = (char)(size >> (8 * 3));
	// new[new_size / 8 + 1] = (char)(size >> (8 * 2));
	// new[new_size / 8 + 2] = (char)(size >> 8);
	// new[new_size / 8 + 3] = (char)size;
	// new[new_size / 8 + 4] = (char)(size >> (8 * 7));
	// new[new_size / 8 + 5] = (char)(size >> (8 * 6));
	// new[new_size / 8 + 6] = (char)(size >> (8 * 5));
	// new[new_size / 8 + 7] = (char)(size >> (8 * 4));

	// uint32_t *buffer = malloc()
	// uint32_t AA = 0x67452301;
	// uint32_t BB = 0xefcdab89;
	// uint32_t CC = 0x98badcfe;
	// uint32_t DD = 0x10325476;
	
	// uint32_t X[16];
	// uint32_t Y;
	// uint32_t Z;

	// uint32_t *blocks = (uint32_t*)new;

	// i = 0;
	// while (i < new_size / 16)
	// {
	// 	j = 0;
	// 	while (j < 16)
	// 	{
	// 		X[j] = blocks[];
	// 	}
	// 	i += 16;
	// }






	// size = 0;
	// i = 0;
	// while (i < new_size / 8 + 8)
	// {
	// 	if (i && i % 8 == 0)
	// 		ft_putchar('\n');
	// 	if (i % 8 == 0)
	// 	{
	// 		ft_putnbr((i * 8) / 512);
	// 		ft_putchar(' ');
	// 	}
	// 	print_bits(new[i], 8);
	// 	ft_putchar(' ');
	// 	msg++;
	// 	i++;
	// }
	// if (opts->s)
	// {
	// 	free(new);
	// 	opts->s = 0;
	// }
	return;
}

static int		parse_opts(char **av, int i, t_md5 *opts)
{
	if (av[i][0] == '-' && !av[i][2])
	{
		if (av[i][1] == 'q')
			opts->q = 1;
		else if (av[i][1] == 'r')
			opts->r = 1;
		else if (av[i][1] == 's' && av[i + 1])
		{
			opts->s = 1;
			opts->input = (unsigned char *)av[i + 1];
			opts->in_size = (ssize_t)ft_strlen(av[i + 1]);
			i++;
		}
		else if (av[i][1] == 'p')
			opts->p = 1;
		else
			return (md5_err_options(av[i][1]));
	}
	else if (!opts->filename)
		opts->filename = av[i];
	else
		return (0);
	return (i + 1);
}

void	md5_opts_init(t_md5 *opts)
{
	opts->q = 0;
	opts->r = 0;
	opts->s = 0;
	opts->p = 0;
	opts->filename = NULL;
	opts->input = NULL;
}

int		md5_prep(int argc, char **argv)
{
	int 	i;
	t_md5	opts;

	md5_opts_init(&opts);
	i = 2;
	while (i < argc)
	{
		if (!(i = parse_opts(argv, i, &opts)))
			return (md5_err_usage());
	}
	md5(opts.input, opts.in_size);
	if (!opts.s)
		free(opts.input);
	return (0);
}
