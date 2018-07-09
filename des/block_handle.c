/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ulliwy <Ulliwy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 12:43:49 by iprokofy          #+#    #+#             */
/*   Updated: 2018/06/28 17:27:09 by Ulliwy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_des.h"

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

void	opts_init(t_opt *opts)
{
	opts->d = 0;
	opts->a = 0;
	opts->iv = 0;
	opts->v = 0;
	opts->prev = 0;
	opts->entered_key = NULL;
	opts->entered_iv = NULL;
	opts->input_file = NULL;
	opts->output_file = NULL;
	opts->in = NULL;
	opts->out = NULL;
	opts->mode[ECB] = 0;
	opts->mode[CBC] = 0;
	opts->mode[ECB3] = 0;
	opts->mode[CBC3] = 0;
	opts->keys[0] = 0;
	opts->keys[1] = 0;
	opts->keys[2] = 0;
}
