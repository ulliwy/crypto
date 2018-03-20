/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iprokofy <iprokofy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 11:44:59 by iprokofy          #+#    #+#             */
/*   Updated: 2018/03/20 13:52:05 by iprokofy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int		err_usage()
{
	ft_putstr("usage: ft_ssl command [command opts] [command args]\n");
	return (0);
}

int		err_usage_commands(char *cmd)
{
	ft_putstr("ft_ssl: Error: '");
	ft_putstr(cmd);
	ft_putstr("' is an invalid command.\n\n");
	ft_putstr("Standard commands:\n\nMessage Digest commands:\n\n");
	ft_putstr("Cipher commands:\nbase64\ndes\ndes-ecb\ndec-cbc\ndes3\ndes3-ecb\ndes3-cbc\n");
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

int 	put_iv_err()
{
	ft_putstr("non-hex digit\n");
	ft_putstr("invalid hex iv value\n");
	return (0);
}

int 	get_iv(t_opt *opts, char *str)
{
	int		i;
	char	c;

	i = 0;
	while (*str && i < 16)
	{
		c = ft_tolower(*str);
		if (!((c >= 'a' && c <= 'f') || (c >= '0' && c <= '9')))
			return (put_iv_err());
		if (c >= 'a' && c <= 'f')
			c = c - 87;
		else
			c = c - '0';
		opts->v = opts->v * 16 + c;
		i++;
		str++;
	}
	//printf("%lu\n", opts->v);
	// while (i < 16)
	// {
	// 	opts->main_key = opts->main_key * 16;
	// 	i++;
	// }
	//printf("%lX\n", opts->main_key);
	return (1);
}

int		parse_opts(char **av, int i, t_opt *opts)
{
	if (av[i][0] == '-' && !av[i][2])
	{
		// if (av[i][1] == 'e')
		// 	opts->e = 1;
		if (av[i][1] == 'd')
			opts->d = 1;
		else if (av[i][1] == 'a')
			opts->a = 1;
		else if (av[i][1] == 'v')
		{
			opts->iv = 1;
			if (!get_iv(opts, av[i + 1]))
				return (0);
			i++;
		}
		else if (av[i][1] == 'i')
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
			return (0);
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
	//opts->main_key = 0;
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
		return (err_usage());
	if (!parse_command(argv, &cmd)) 
		return (err_usage_commands(argv[1]));
	i = 2;
	while (i < argc)
	{
		if (!(i = parse_opts(argv, i, &opts)))
			return (err_usage());
	}

	//printf("%lu\n", opts.v);
	//print_opts(opts);
	if (cmd.b64)
		b64(&opts);
	else if ((cmd.cbc || cmd.cbc3) && (!opts.iv))
	{
		ft_putstr("iv undefined\n");
		return (0);
	}
	else if (cmd.ecb || cmd.cbc || cmd.ecb3 || cmd.cbc3)
		des_prep(opts);
	return (0);
}
