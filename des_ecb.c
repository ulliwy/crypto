/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_ecb.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iprokofy <iprokofy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 12:46:00 by iprokofy          #+#    #+#             */
/*   Updated: 2017/12/18 13:11:20 by iprokofy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

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

unsigned long	permute_bits(unsigned long k, unsigned long	keys[16])
{
	unsigned long	k_plus;
	unsigned long	one;
	unsigned long	c0;
	unsigned long	d0;
	int				i;

	i = 0;
	k_plus = 0;
	one = 1;
	// ft_putstr("original: ");
	// print_bits(k, 8);
	// ft_putstr("\n");
	while (i < 56)
	{
		k_plus = k_plus | ((one << (64 - g_pc1[i])) & k ? one << (55 - i) : 0);
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

	return (k);
}

void	des_ecb_decode(char *in, int fd)
{
	ft_putstr_fd(in, fd);
}

void	des_ecb_encode(unsigned char *in, int fd, ssize_t r)
{
	int 	i;
	int 	j;

	i = 0;
	while (i < r)
	{
		j = 0;
		while (j < 64)
		{
			in[] = k_plus | ((one << (64 - g_pc1[i])) & k ? one << (55 - i) : 0);
			i++;
		}

		i = i + 16;
	}
}

void	des_ecb(t_opt opts)
{
	unsigned long	keys[16];
	char	*input;
	int 	fd;
	ssize_t r;

	permute_bits(opts.main_key, keys);
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
	if (opts.d)
		des_ecb_decode(input, fd);
	else
		des_ecb_encode((unsigned char *)input, fd, r);
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
