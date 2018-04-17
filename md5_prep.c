/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_prep.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iprokofy <iprokofy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 14:34:02 by iprokofy          #+#    #+#             */
/*   Updated: 2018/04/17 16:52:57 by iprokofy         ###   ########.fr       */
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

static int		parse_opts(char **av, int i, t_md5 *opts)
{
	if (av[i][0] == '-' && !av[i][2])
	{
		if (av[i][1] == 'q')
			opts->q = 1;
		else if (av[i][1] == 'r')
			opts->r = 1;
		else if (av[i][1] == 's')
		{
			(opts->strs)[(opts->str_num)++] = av[i + 1];
			i++;
		}
		else if (av[i][1] == 'p')
			opts->stdinn = get_from_fd(0, &(opts->in_size));
		else
			return (md5_err_options(av[i][1]));
	}
	else
		return (0);
	return (i + 1);
}

void	md5_opts_init(t_md5 *opts)
{
	opts->str_num = 0;
	opts->q = 0;
	opts->r = 0;
	opts->stdinn = NULL;
}

int		md5(int argc, char **argv)
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
	return (0);
}
