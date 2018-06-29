/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_gen.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ulliwy <Ulliwy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 15:38:33 by iprokofy          #+#    #+#             */
/*   Updated: 2018/06/28 17:27:32 by Ulliwy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ssl.h"

int				get_value(char *c)
{
	if (!((*c >= 'a' && *c <= 'f') || (*c >= '0' && *c <= '9')))
		return (0);
	if (*c >= 'a' && *c <= 'f')
		*c = *c - 87;
	else
		*c = *c - '0';
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
		key = key | (((1UL << (56 - g_pc2[i])) &
				(c0 | d0)) ? 1UL << (47 - i) : 0);
		i++;
	}
	return (key);
}

void			permut_c0d0(unsigned long *c0, unsigned long *d0,
			unsigned long keys[16])
{
	int				i;
	unsigned long	cl;
	unsigned long	cr;
	unsigned long	dl;
	unsigned long	dr;

	i = 0;
	while (i < 16)
	{
		cr = *c0 >> (28 - g_shifts[i]);
		cl = *c0 << g_shifts[i];
		*c0 = (cl | cr) & ((1UL << 56) - (1UL << 28));
		dr = *d0 >> (28 - g_shifts[i]);
		dl = *d0 << g_shifts[i];
		*d0 = (dl | dr) & ((1UL << 28) - 1UL);
		keys[i] = permut_pc2(*c0, *d0);
		i++;
	}
}

int				get_keys3(t_opt *opts)
{
	int		i;
	int		k;
	char	c;

	i = 0;
	k = 0;
	while (opts->entered_key[i] && opts->entered_key[i] != '\n' && i < 48)
	{
		c = ft_tolower(opts->entered_key[i]);
		if (!get_value(&c))
			return (put_key_err());
		opts->keys[k] = opts->keys[k] * 16 + c;
		i++;
		if (i && (i % 16 == 0))
			k++;
	}
	while (i < 48)
	{
		opts->keys[k] = opts->keys[k] * 16;
		i++;
		if (i && (i % 16 == 0))
			k++;
	}
	return (1);
}

int				get_key(t_opt *opts)
{
	int		len;
	int		i;
	char	c;

	i = 0;
	len = ft_strlen(opts->entered_key);
	if (opts->entered_key[len - 1] == '\n')
		len--;
	while (i < len && i < 16)
	{
		c = ft_tolower(opts->entered_key[i]);
		if (!get_value(&c))
			return (put_key_err());
		opts->keys[0] = opts->keys[0] * 16 + c;
		i++;
	}
	while (i++ < 16)
		opts->keys[0] = opts->keys[0] * 16;
	return (1);
}
