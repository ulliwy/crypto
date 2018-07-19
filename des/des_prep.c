/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_prep.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iprokofy <iprokofy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/19 09:58:32 by iprokofy          #+#    #+#             */
/*   Updated: 2018/07/19 10:06:56 by iprokofy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_des.h"
#include "ft_err.h"
#include "libft.h"

char	giv(char c)
{
	if (c >= 'A' && c <= 'Z')
		return (c - 65);
	else if (c >= 'a' && c <= 'z')
		return (c - 71);
	else if (c >= '0' && c <= '9')
		return (c + 4);
	else if (c == '+')
		return (62);
	else
		return (63);
}

int		get_iv(t_opt *opts, char *str)
{
	int		i;
	char	c;

	i = 0;
	if (!str)
		return (put_iv_err(2));
	while (*str && i < 16)
	{
		c = ft_tolower(*str);
		if (!((c >= 'a' && c <= 'f') || (c >= '0' && c <= '9')))
			return (put_iv_err(1));
		if (c >= 'a' && c <= 'f')
			c = c - 87;
		else
			c = c - '0';
		opts->v = opts->v * 16 + c;
		i++;
		str++;
	}
	while (i++ < 16)
		opts->v = opts->v * 16;
	return (1);
}

int		parse_opts2(char **av, int i, t_opt *opts)
{
	if (av[i][1] == 'i')
	{
		opts->input_file = av[i + 1];
		i++;
	}
	else if (av[i][1] == 'o')
	{
		opts->output_file = av[i + 1];
		i++;
	}
	else if (av[i][1] == 'k')
	{
		opts->entered_key = av[i + 1];
		i++;
	}
	else
		return (err_options(av[i][1]));
	return (i + 1);
}

int		parse_opts(char **av, int i, t_opt *opts)
{
	if (av[i][0] == '-' && !av[i][2])
	{
		if (av[i][1] == 'd')
			opts->d = 1;
		else if (av[i][1] == 'a')
			opts->a = 1;
		else if (av[i][1] == 'e')
			;
		else if (av[i][1] == 'v')
		{
			opts->iv = 1;
			if (!get_iv(opts, av[i + 1]))
				return (-1);
			i++;
		}
		else
			return (parse_opts2(av, i, opts));
	}
	else
		return (0);
	return (i + 1);
}
