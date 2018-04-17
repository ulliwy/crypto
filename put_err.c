/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_err.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ulliwy <Ulliwy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 15:26:11 by iprokofy          #+#    #+#             */
/*   Updated: 2018/04/16 16:04:49 by Ulliwy           ###   ########.fr       */
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
	ft_putstr("Standard commands:\n\n");
	ft_putstr("Message Digest commands:\nmd5\nsha256\n\n");
	ft_putstr("Cipher commands:\nbase64\ndes\ndes-ecb\ndec-cbc");
	ft_putstr("\ndes3\ndes3-ecb\ndes3-cbc\n");
	return (0);
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

void	*put_stream_err(void)
{
	ft_putstr("Invalid character in input stream.\n");
	return (NULL);
}
