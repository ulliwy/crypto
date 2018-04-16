/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ulliwy <Ulliwy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 11:44:59 by iprokofy          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2018/04/16 12:53:22 by Ulliwy           ###   ########.fr       */
=======
/*   Updated: 2018/03/26 16:26:51 by iprokofy         ###   ########.fr       */
>>>>>>> b2711e10f6efb959f01520705504c9e25fa64363
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int		parse_command(char **argv, t_cmd *cmd)
{
	if (!(ft_strcmp(argv[1], "base64")))
		cmd->b64 = 1;
	else if (!(ft_strcmp(argv[1], "des-ecb")))
		cmd->ecb = 1;
	else if (!(ft_strcmp(argv[1], "des")))
		cmd->ecb = 1;
	else if (!(ft_strcmp(argv[1], "des-cbc")))
		cmd->cbc = 1;
	else if (!(ft_strcmp(argv[1], "des3")))
		cmd->ecb3 = 1;
	else if (!(ft_strcmp(argv[1], "des3-ecb")))
		cmd->ecb3 = 1;
	else if (!(ft_strcmp(argv[1], "des3-cbc")))
		cmd->cbc3 = 1;
	else
		return (0);
	return (1);
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

int		main(int argc, char **argv)
{
	t_cmd	cmd;
	t_opt	opts;
	int		i;

	opts_init(&opts, &cmd);
	cmd_init(&cmd);
	if (argc < 2)
		return (err_usage(0));
	if (!parse_command(argv, &cmd))
		return (err_usage_commands(argv[1]));
	i = 2;
	while (i < argc)
	{
		if (!(i = parse_opts(argv, i, &opts)) || i == -1 || i == -2)
			return (err_usage(i));
	}
	if (cmd.b64)
		b64(&opts);
	else if (cmd.ecb || cmd.cbc || cmd.ecb3 || cmd.cbc3)
		des_prep(opts);
	return (0);
}
