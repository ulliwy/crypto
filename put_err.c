/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_err.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ulliwy <Ulliwy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 15:26:11 by iprokofy          #+#    #+#             */
/*   Updated: 2018/07/05 14:48:33 by Ulliwy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "stdio.h"

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

void	put_open_err(char *name)
{
	char	*err_msg;
	int		len;

	len = ft_strlen(name);
	err_msg = (char *)ft_memalloc(len + 18);
	ft_strcpy(err_msg, "Unable to open \'");
	ft_strcpy(err_msg + 16, name);
	err_msg[16 + len] = '\'';
	perror(err_msg);
	free(err_msg);
}

int		put_key_err(void)
{
	ft_putstr("non-hex digit\n");
	ft_putstr("invalid hex key value\n");
	return (0);
}

void	hash_open_err(char *name, char *func_name, int name_len)
{
	char	*err_msg;
	int		len;

	len = ft_strlen(name);
	err_msg = (char *)ft_memalloc(len + name_len + 2);
	ft_strcpy(err_msg, func_name);
	ft_strcpy(err_msg + name_len, ": ");
	ft_strcpy(err_msg + name_len + 2, name);
	perror(err_msg);
	free(err_msg);
}
