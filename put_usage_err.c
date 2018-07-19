/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_usage_err.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iprokofy <iprokofy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/19 10:21:52 by iprokofy          #+#    #+#             */
/*   Updated: 2018/07/19 10:31:32 by iprokofy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
	ft_putstr("Standard commands:\n\n");
	ft_putstr("Message Digest commands:\nmd5\nsha256\n\n");
	ft_putstr("Cipher commands:\nbase64\ndes\ndes-ecb\ndec-cbc");
	ft_putstr("\ndes3\ndes3-ecb\ndes3-cbc\n");
	return (0);
}

int		md5_err_usage(char *command)
{
	ft_putstr("usage: ft_ssl ");
	ft_putstr(command);
	ft_putstr(" [-pqr] [-s string] [files ...]\n");
	return (1);
}
