/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_encode.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iprokofy <iprokofy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 15:47:06 by iprokofy          #+#    #+#             */
/*   Updated: 2018/03/23 15:56:38 by iprokofy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

unsigned long	half_permut(unsigned long temp, unsigned long keys[16])
{
	unsigned long	l[17];
	unsigned long	r[17];
	int				j;

	l[0] = temp >> 32;
	r[0] = temp & ((1UL << 32) - 1UL);
	j = 1;
	while (j <= 16)
	{
		l[j] = r[j - 1];
		r[j] = l[j - 1] ^ ff(r[j - 1], keys[j - 1]);
		j++;
	}
	r[16] = (r[16] << 32) | l[16];
	j = 0;
	temp = 0;
	while (j < 64)
	{
		temp = temp | (((1UL << (64 - g_ip_1[j])) & r[16]) ?
				1UL << (63 - j) : 0);
		j++;
	}
	return (temp);
}

unsigned long	des_encryption(unsigned long msg, unsigned long keys[16],
		t_opt opts, int i)
{
	unsigned long	temp;
	int				j;

	msg = reverse_bits(msg);
	if (!i && opts.cmd->cbc)
		msg = msg ^ opts.v;
	if (i > 0 && opts.cmd->cbc)
		msg = reverse_bits(opts.prev) ^ msg;
	temp = 0;
	j = 0;
	while (j < 64)
	{
		temp = temp | (((1UL << (64 - g_ip[j])) & msg) ? 1UL << (63 - j) : 0);
		j++;
	}
	msg = reverse_bits(half_permut(temp, keys));
	return (msg);
}

void			des_ecb_encode(ssize_t size, t_opt opts)
{
	unsigned long	keys[3][16];
	unsigned long	*msg;
	int				i;

	pad(opts.in, size);
	key_gen(&keys, &opts);
	msg = (unsigned long *)opts.in;
	i = 0;
	while (i < size / 8 + 1)
	{
		if (i > 0)
			opts.prev = msg[i - 1];
		msg[i] = des_encryption(msg[i], keys[0], opts, i);
		if (opts.cmd->ecb3 || opts.cmd->cbc3)
		{
			msg[i] = reverse_bits(des_decryption(msg[i], keys[1], opts, i));
			msg[i] = des_encryption(msg[i], keys[2], opts, i);
		}
		i++;
	}
	opts.in = (unsigned char *)msg;
	if (opts.a)
		b64_encode(&opts, (size / 8 + 1) * sizeof(unsigned long));
	else
		write(opts.fd, msg, (size / 8 + 1) * sizeof(unsigned long));
}
