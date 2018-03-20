/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iprokofy <iprokofy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 12:43:49 by iprokofy          #+#    #+#             */
/*   Updated: 2018/03/20 15:28:00 by iprokofy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

unsigned long	reverse_bits(unsigned long msg)
{
	unsigned long	tmp;

	tmp = 0;
	tmp = tmp | (msg & 255) << (7 * 8);
	tmp = tmp | (msg & 65280) << (5 * 8);
	tmp = tmp | (msg & 16711680) << (3 * 8);
	tmp = tmp | (msg & 4278190080) << (1 * 8);
	tmp = tmp | ((msg >> 8) & 4278190080);
	tmp = tmp | ((msg >> (3 * 8)) & 16711680);
	tmp = tmp | ((msg >> (5 * 8)) & 65280);
	tmp = tmp | ((msg >> (7 * 8)) & 255);
	return (tmp);
}

void			pad(unsigned char *in, ssize_t size)
{
	unsigned char	pads;
	int				i;

	pads = 8 - (unsigned char)(size % 8);
	i = 0;
	while (i < pads)
	{
		in[size + i] = pads;
		i++;
	}
}
