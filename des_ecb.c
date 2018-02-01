/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_ecb.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iprokofy <iprokofy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 12:46:00 by iprokofy          #+#    #+#             */
/*   Updated: 2018/01/31 16:30:16 by iprokofy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include <stdio.h>

int		put_key_err()
{
	ft_putstr("iv undefined\n");
	return (0);
}

int		get_key(t_opt *opts)
{
	int		len;
	int		i;
	char	c;

	i = 0;
	len = ft_strlen(opts->entered_key);
	if (opts->entered_key[len - 1] == '\n')
		len--;
	while (i < len)
	{
		c = ft_tolower(opts->entered_key[i]);
		if (!((c >= 'a' && c <= 'f') || (c >= '0' && c <= '9')))
			return (put_key_err());
		if (c >= 'a' && c <= 'f')
			c = c - 87;
		else
			c = c - '0';
		opts->main_key = opts->main_key * 16 + c;
		i++;
	}
	return (1);
}

unsigned long	permut_pc2(unsigned long c0, unsigned long d0)
{
	unsigned long	key;
	int				i;

	i = 0;
	key = 0;
	while (i < 48)
	{
		key = key | (((1UL << (56 - g_pc2[i])) & (c0 | d0)) ? 1UL << (47 - i) : 0);
		i++;
	}
	return (key);
}

void	permut_c0d0(unsigned long *c0, unsigned long *d0, unsigned long	keys[16])
{
	int i;
	unsigned long	cl;
	unsigned long	cr;
	unsigned long	dl;
	unsigned long	dr;

	i = 0;
	while (i < 16)
	{
		// ft_putstr("c");
		// ft_putnbr(i + 1);
		// ft_putstr(" -> ");
		cr = *c0 >> (28 - g_shifts[i]);
		cl = *c0 << g_shifts[i];
		*c0 = (cl | cr) & ((1UL << 56) - (1UL << 28));
		// print_bits(*c0, 7);
		// ft_putstr("\n");

		// ft_putstr("d");
		// ft_putnbr(i + 1);
		// ft_putstr(" -> ");
		dr = *d0 >> (28 - g_shifts[i]);
		dl = *d0 << g_shifts[i];
		*d0 = (dl | dr) & ((1UL << 28) - 1UL);
		// print_bits(*d0, 7);
		// ft_putstr("\n");
		keys[i] = permut_pc2(*c0, *d0);
		// ft_putstr("key");
		// ft_putnbr(i + 1);
		// ft_putstr(" -> ");
		// print_bits(keys[i], 6);
		// ft_putstr("\n\n");
		i++;
	}
}

void	create_subkeys(unsigned long k, unsigned long	keys[16])
{
	unsigned long	k_plus;
	unsigned long	c0;
	unsigned long	d0;
	int				i;

	i = 0;
	k_plus = 0;
	while (i < 56)
	{
		k_plus = k_plus | ((1UL << (64 - g_pc1[i])) & k ? 1UL << (55 - i) : 0);
		i++;
	}
	c0 = ((1UL << 56) - (1UL << 28)) & k_plus;
	d0 = ((1UL << 28) - 1UL) & k_plus;

	// ft_putstr("k_plus: ");
	// print_bits(k_plus, 7);
	// ft_putstr("\n");
	// ft_putstr("c0:     ");
	// print_bits(c0, 7);
	// ft_putstr("\n");
	// ft_putstr("d0:     ");
	// print_bits(d0, 7);
	// ft_putstr("\n");
	permut_c0d0(&c0, &d0, keys);
}

void	des_ecb_decode(char *in, int fd)
{
	ft_putstr_fd(in, fd);
}

unsigned long	ff(unsigned long r, unsigned long k)
{
	unsigned long	er;
	unsigned long	result;
	int 			i;

	i = 0;
	er = 0;
	result = 0;
	while (i < 48)
	{
		er = er | ((1UL << (32 - g_ebit[i])) & r ? 1UL << (47 - i) : 0);
		i++;
	}
	// ft_putstr("r:   ");
	// print_bits(r, 4);
	// ft_putstr("\n");
	// ft_putstr("er:  ");
	// print_bits(er, 6);
	// ft_putstr("\n");
	er = er ^ k;
	// ft_putstr("xor: ");
	// print_bits(er, 6);
	// ft_putstr("\n");
	// ft_putstr("\n");
	i = 0;
	unsigned long p4 = 0;
	unsigned long f = 0;
	while (i < 8)
	{
		unsigned long p1 = (er >> ((7 - i) * 6)) & 63;
		unsigned long p2 = (1 & p1) | ((p1 >> 4) & 2);
		unsigned long p3 = (p1 >> 1) & 15;
		p4 = (p4 << 4) | (g_ss[i][p2 * 16 + p3]);
		// printf("row: %lu, col: %lu, val: %lu\n", p2, p3, (p2) * 16 + p3);
		// ft_putstr("f: ");
		// print_bits(f, 4);
		// ft_putstr("\n");
		// ft_putstr("row: ");
		// print_bits(p2, 6);
		// ft_putstr("\n");
		// ft_putstr("col: ");
		// print_bits(p3, 6);
		// ft_putstr("\n");
		// ft_putstr("val: ");
		// print_bits(p4, 4);
		// ft_putstr("\n");
		// ft_putstr("\n");
		i++;
	}
	int j = 0;
	while (j < 32)
	{
		f = (f << 1UL) | ((1UL << (32 - g_p[j])) & p4 ? 1UL : 0);
		j++;
		// ft_putstr("f: ");
		// print_bits(f, 4);
		// ft_putstr("\n");
	}
	//print_bits(f, 4);
	//ft_putstr("\n\n");


	return (f);
}

void	des_ecb_encode(unsigned char *in, int fd, ssize_t size, t_opt opts)
{
	unsigned long	keys[16];
	unsigned long	*msg;
	unsigned long	temp;;
	int 			i;
	int 			j;
	unsigned long	l[17];
	unsigned long	r[17];

	create_subkeys(opts.main_key, keys);
	i = 0;
	fd = 0;
	msg = (unsigned long *)in;
	//printf("message: <%s>\n", in);
	printf("message: <%s>\n", (unsigned char *)msg);
	for (i = 0; i < size; ++i) {
		if (i && i % 8 == 0)
			printf(" ");
		printf("%c%X ", in[i], in[i]);
	}
	printf("\n");
	// for (i = 0; i < size; ++i) {
	// 	if (i && i % 8 == 0)
	// 		printf(" ");
	// 	printf("%c", in[i]);
	// }
	// printf("\n");
	i = 0;
	while (i < size / 8)
	{
		//printf("%lX\n", msg[i]);
		// ft_putstr("msg:    ");
		// print_bits(msg[i], 4);
		// ft_putstr("\n");
		temp = 0;
		j = 0;
		//initial permutation
		while (j < 64)
		{
			temp = temp | (((1UL << (64 - g_ip[j])) & msg[i]) ? 1UL << (63 - j) : 0);
			j++;
		}
		l[0] = temp >> 32;
		r[0] = temp & ((1UL << 32) - 1UL);
		//msg[i] = temp;
		j = 1;
		while (j <= 16)
		{
			l[j] = r[j - 1];
			// ft_putstr("ff: ");
			// print_bits(ff(r[j - 1], keys[j - 1]), 4);
			// ft_putstr("\n");
			// ft_putstr("l : ");
			// print_bits(l[j - 1], 4);
			// ft_putstr("\n\n");
			r[j] = l[j - 1] ^ ff(r[j - 1], keys[j - 1]);
			
			j++;
			
		}

		r[16] = (r[16] << 32) | l[16];
		j = 0;
		temp = 0;
		while (j < 64)
		{
			temp = temp | (((1UL << (64 - g_ip_1[j])) & r[16]) ? 1UL << (63 - j) : 0);
			j++;
		}
		// ft_putstr("temp: ");
		// print_bits(temp, 8);
		// ft_putstr("\n");
		// ft_putstr("r16: ");
		// print_bits(r[16], 4);
		//ft_putstr("\n\n");
		msg[i] = temp;
		i++;
	}
	in = (unsigned char *)msg;
	for (i = 0; i < size; ++i) {
		if (i && i % 8 == 0)
			printf(" ");
		printf("%X", in[i]);
	}
	printf("\n");
}

void	des_ecb(t_opt opts)
{
	char	*input;
	int 	fd;
	ssize_t r;

	
	if (!opts.input_file)
		input = get_from_fd(0, &r);
	else
	{
		if ((fd = open(opts.input_file, O_RDONLY)) == -1)
		{
			put_open_err(opts.input_file);
			return ;
		}
	 	input = get_from_fd(fd, &r);
	 	close(fd);
	}
	if (!opts.output_file)
		fd = 1;
	else
	{
		if ((fd = open(opts.output_file, O_CREAT | O_WRONLY | O_TRUNC, 0644)) == -1)
		{
			put_open_err(opts.output_file);
			return ;
		}
	}
	printf("input: <%s>, size: %zd\n", input, r);
	// input[15] = 0x01;
	// input[14] = 0x23;
	// input[13] = 0x45;
	// input[12] = 0x67;
	// input[11] = 0x89;
	// input[10] = 0xAB;
	// input[9] = 0xCD;
	// input[8] = 0xEF;
	// input[7] = 0x01;
	// input[6] = 0x23;
	// input[5] = 0x45;
	// input[4] = 0x67;
	// input[3] = 0x89;
	// input[2] = 0xAB;
	// input[1] = 0xCD;
	// input[0] = 0xEF;
	//printf("input: <%s>, size: %zd\n", input, r);
	// unsigned long *k = (unsigned long *)input;
	// ft_putstr("msg: ");
	// print_bits(*k, 4);
	// ft_putstr("\n");
	if (opts.d)
		des_ecb_decode(input, fd);
	else
		des_ecb_encode((unsigned char *)input, fd, r, opts);
	close(fd);
	free(input);

	// int i= 0;
	// while (i < 16)
	// {
	// 	printf("%d: %lu\n", i+ 1, keys[i]);
	// 	i++;
	// }
}

void	des_prep(t_opt opts)
{
	int		allocated;

	allocated = 0;
	if (!opts.entered_key)
	{
		opts.entered_key = (char *)ft_memalloc(100);
		ft_putstr("enter des key in hex: ");
		read(1, opts.entered_key, 100);
		allocated = 1;
	}
	if (!get_key(&opts))
		return ;
	des_ecb(opts);
	if (allocated)
		free(opts.entered_key);
}
