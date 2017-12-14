/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_ecb.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iprokofy <iprokofy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 12:46:00 by iprokofy          #+#    #+#             */
/*   Updated: 2017/12/14 14:33:54 by iprokofy         ###   ########.fr       */
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
	if (opts->entered_key[len -1] == '\n')
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

unsigned long	permute_bits(unsigned long k)
{
	unsigned long	k_plus;
	unsigned long	one;
	int				i;
	unsigned long	temp;

	i = 0;
	k_plus = 0;
	one = 1;
	ft_putstr("original: ");
	print_bits(k);
	ft_putstr("\n");
	while (i < 56)
	{
		ft_putnbr(i);
		ft_putstr(": ");
		temp = ((one << (64 - g_pc1[i])) & k) << (64 - g_pc1[i] - (i + 1));
		print_bits(temp);
		ft_putstr("\n");
		i++;
	}
	return (k);
}

void	des_ecb(t_opt opts)
{
	//unsigned long	keys[16];
	unsigned long	k_plus;

	k_plus = permute_bits(opts.main_key);
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
