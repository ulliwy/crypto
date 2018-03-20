/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iprokofy <iprokofy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 11:44:59 by iprokofy          #+#    #+#             */
/*   Updated: 2018/03/20 16:34:13 by iprokofy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int		err_usage(int type)
{
	if (!type)
		ft_putstr("usage: ft_ssl command [command opts] [command args]\n");
	return (0);
}

int		err_options(char cmd)
{
	ft_putstr("ft_ssl: Error: '");
	ft_putchar(cmd);
	ft_putstr("' is an invalid option.\n");
	ft_putstr("Available options: edkvio\n");
	return (-2);
}

int		err_usage_commands(char *cmd)
{
	ft_putstr("ft_ssl: Error: '");
	ft_putstr(cmd);
	ft_putstr("' is an invalid command.\n\n");
	ft_putstr("Standard commands:\n\nMessage Digest commands:\n\n");
	ft_putstr("Cipher commands:\nbase64\ndes\ndes-ecb\ndec-cbc");
	ft_putstr("\ndes3\ndes3-ecb\ndes3-cbc\n");
	return (0);
}

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

int		put_iv_err(int type)
{
	if (type == 1)
	{
		ft_putstr("non-hex digit\n");
		ft_putstr("invalid hex iv value\n");
	}
	else
		ft_putstr("iv undefined\n");
	return (0);
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

void	opts_init(t_opt *opts, t_cmd *cmd)
{
	opts->d = 0;
	opts->a = 0;
	opts->iv = 0;
	opts->v = 0;
	opts->entered_key = NULL;
	opts->input_file = NULL;
	opts->output_file = NULL;
	opts->in = NULL;
	opts->out = NULL;
	opts->cmd = cmd;
	opts->keys[0] = 0;
	opts->keys[1] = 0;
	opts->keys[2] = 0;
}

void	cmd_init(t_cmd *cmd)
{
	cmd->b64 = 0;
	cmd->ecb = 0;
	cmd->cbc = 0;
	cmd->ecb3 = 0;
	cmd->cbc3 = 0;
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
	else if ((cmd.cbc || cmd.cbc3) && (!opts.iv))
		return (put_iv_err(2));
	else if (cmd.ecb || cmd.cbc || cmd.ecb3 || cmd.cbc3)
		des_prep(opts);
	return (0);
}
