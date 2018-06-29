/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_decode.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ulliwy <Ulliwy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 15:47:06 by iprokofy          #+#    #+#             */
/*   Updated: 2018/06/28 17:27:17 by Ulliwy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ssl.h"

unsigned long	rev_half_permut(unsigned long temp, unsigned long keys[16])
{
	unsigned long	l[17];
	unsigned long	r[17];
	int				j;

	r[16] = temp >> 32;
	l[16] = temp & ((1UL << 32) - 1UL);
	j = 16;
	while (j >= 1)
	{
		l[j - 1] = r[j] ^ ff(l[j], keys[j - 1]);
		r[j - 1] = l[j];
		j--;
	}
	l[0] = (l[0] << 32) | r[0];
	j = 0;
	temp = 0;
	while (j < 64)
	{
		temp = temp | ((l[0] & 1UL) << (64 - g_ip[63 - j]));
		l[0] = l[0] >> 1;
		j++;
	}
	return (temp);
}

unsigned long	des_decryption(unsigned long msg, unsigned long keys[16],
		t_opt opts, int i)
{
	unsigned long	temp;
	int				j;

	msg = reverse_bits(msg);
	temp = 0;
	j = 0;
	while (j < 64)
	{
		temp = temp | ((msg & 1UL) << (64 - g_ip_1[63 - j]));
		msg = msg >> 1;
		j++;
	}
	temp = rev_half_permut(temp, keys);
	if (!i && opts.cmd->cbc)
		temp = temp ^ opts.v;
	if (i > 0 && opts.cmd->cbc)
		temp = temp ^ reverse_bits(opts.prev);
	return (temp);
}

unsigned long	additional(unsigned long *msg, int i, t_opt *opts,
		unsigned long keys[3][16])
{
	unsigned long res;

	res = msg[i];
	if (i > 0)
		opts->prev = msg[i - 1];
	if (opts->cmd->ecb3 || opts->cmd->cbc3)
	{
		res = reverse_bits(des_decryption(res, keys[2], *opts, i));
		res = des_encryption(res, keys[1], *opts, i);
	}
	res = des_decryption(res, keys[0], *opts, i);
	return (res);
}

void			des_ecb_decode(ssize_t size, t_opt opts)
{
	unsigned long	keys[3][16];
	unsigned long	*msg;
	int				i;
	unsigned long	*res;
	int				val;

	key_gen(&keys, &opts);
	if (opts.a)
		msg = (unsigned long *)b64_decode(opts.in, &size);
	else
		msg = (unsigned long *)opts.in;
	res = (unsigned long *)ft_memalloc(size);
	i = 0;
	while (i < size / 8)
	{
		res[i] = additional(msg, i, &opts, keys);
		val = ((res[i] & 255) > 8) ? 8 : res[i] & 255;
		res[i] = reverse_bits(res[i]);
		i++;
	}
	write(opts.fd, res, sizeof(*res) * i - val);
	free(res);
	if (opts.a)
		free(msg);
}
