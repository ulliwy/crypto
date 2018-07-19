/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iprokofy <iprokofy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 11:44:59 by iprokofy          #+#    #+#             */
/*   Updated: 2018/07/19 10:33:54 by iprokofy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "libft.h"
#include "ft_des.h"
#include "ft_err.h"

void	cmd_init(t_cmd *cmd)
{
	cmd->b64 = 0;
	cmd->ecb = 0;
	cmd->cbc = 0;
	cmd->ecb3 = 0;
	cmd->cbc3 = 0;
	cmd->hashing = -1;
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
	else if (!(ft_strcmp(argv[1], "md5")))
		cmd->hashing = MD5;
	else if (!(ft_strcmp(argv[1], "sha256")))
		cmd->hashing = SHA256;
	else if (!(ft_strcmp(argv[1], "sha512")))
		cmd->hashing = SHA512;
	else
		return (0);
	return (1);
}

void	get_mode(t_cmd cmd, t_opt *opts)
{
	if (cmd.ecb)
		opts->mode[0] = 1;
	else if (cmd.cbc)
		opts->mode[1] = 1;
	else if (cmd.ecb3)
		opts->mode[2] = 1;
	else if (cmd.cbc3)
		opts->mode[3] = 1;
}

int		main(int argc, char **argv)
{
	t_cmd	cmd;
	t_opt	opts;
	int		i;

	cmd_init(&cmd);
	opts_init(&opts);
	if (argc < 2)
		return (err_usage(0));
	if (!parse_command(argv, &cmd))
		return (err_usage_commands(argv[1]));
	get_mode(cmd, &opts);
	i = 2;
	while (i < argc && cmd.hashing == -1)
	{
		if (!(i = parse_opts(argv, i, &opts)) || i == -1 || i == -2)
			return (err_usage(i));
	}
	if (cmd.b64)
		b64(&opts);
	else if (cmd.ecb || cmd.cbc || cmd.ecb3 || cmd.cbc3)
		des_prep(opts);
	else if (cmd.hashing != -1)
		hash_prep(argc, argv, cmd.hashing);
	return (0);
}
