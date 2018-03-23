/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iprokofy <iprokofy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 12:46:00 by iprokofy          #+#    #+#             */
/*   Updated: 2018/03/23 15:53:53 by iprokofy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	create_subkeys(unsigned long k, unsigned long keys[16])
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
	permut_c0d0(&c0, &d0, keys);
}

void	key_gen(unsigned long (*keys)[3][16], t_opt *opts)
{
	if (opts->cmd->ecb3 || opts->cmd->cbc3)
	{
		create_subkeys((*opts).keys[0], (*keys)[0]);
		create_subkeys((*opts).keys[1], (*keys)[1]);
		create_subkeys((*opts).keys[2], (*keys)[2]);
	}
	else
		create_subkeys((*opts).keys[0], (*keys)[0]);
}

void	des(t_opt *opts)
{
	ssize_t r;

	opts->fd = !opts->input_file ? 0 : open(opts->input_file, O_RDONLY);
	if (opts->fd == -1)
		return (put_open_err(opts->input_file));
	opts->in = (unsigned char *)get_from_fd(opts->fd, &r);
	close(opts->fd);
	if (!opts->output_file)
		opts->fd = 1;
	else if ((opts->fd = open(opts->output_file,
			O_CREAT | O_WRONLY | O_APPEND | O_TRUNC, 0644)) == -1)
		return (put_open_err(opts->output_file));
	if (opts->cmd->cbc3)
		opts->cmd->cbc = 1;
	if (opts->d)
		des_ecb_decode(r, *opts);
	else
		des_ecb_encode(r, *opts);
	close(opts->fd);
	free(opts->in);
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
	if (opts.cmd->ecb3 || opts.cmd->cbc3)
	{
		if (!get_keys3(&opts))
			return ;
	}
	else if (!get_key(&opts))
		return ;
	des(&opts);
	if (allocated)
		free(opts.entered_key);
}
