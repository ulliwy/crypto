/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ulliwy <Ulliwy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 11:44:59 by iprokofy          #+#    #+#             */
/*   Updated: 2017/12/08 14:48:52 by Ulliwy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include <stdio.h>

int		err_usage()
{
	ft_putstr("usage: ft_ssl command [command opts] [command args]\n");
	return (0);
}

int		parse_command(char **argv, t_cmd *cmd)
{
	if (!(ft_strcmp(argv[1], "base64")))
		cmd->b64 = 1;
	else
		return (0);
	return (1);
}

int		main(int argc, char **argv)
{
	t_cmd	cmd;

	if (argc < 2)
		return (err_usage());
	if (!parse_command(argv, &cmd))
		return (err_usage());
	if (!parse_opts(argv, ))
}