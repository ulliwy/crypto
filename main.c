/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iprokofy <iprokofy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 11:44:59 by iprokofy          #+#    #+#             */
/*   Updated: 2017/12/12 16:23:01 by iprokofy         ###   ########.fr       */
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

int		parse_opts(char **av, int i, t_opt *opts)
{
	if (av[i][0] == '-' && !av[i][2])
	{
		if (av[i][1] == 'e')
			opts->e = 1;
		else if (av[i][1] == 'd')
			opts->d = 1;
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
		else
			return (0);
	}
	else
		return (0);
	return (i + 1);
}

void	opts_init(t_opt *opts)
{
	opts->e = 1;
	opts->d = 0;
	opts->input_file = NULL;
	opts->output_file = NULL;
}

void	print_opts(t_opt o)
{
	printf("e: %d\n", o.e);
	printf("d: %d\n", o.d);
	printf("input_file: <%s>\n", o.input_file);
	printf("output_file: <%s>\n", o.output_file);
}

int		main(int argc, char **argv)
{
	t_cmd	cmd;
	t_opt	opts;
	int		i;

	opts_init(&opts);
	if (argc < 2)
		return (err_usage());
	if (!parse_command(argv, &cmd))
		return (err_usage());
	i = 2;
	while (i < argc)
	{
		if (!(i = parse_opts(argv, i, &opts)))
			return (err_usage());
	}
	//print_opts(opts);
	if (cmd.b64)
		b64(opts);
	return (0);
}
