/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_err.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iprokofy <iprokofy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 15:26:11 by iprokofy          #+#    #+#             */
/*   Updated: 2018/07/19 10:31:55 by iprokofy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "stdio.h"

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
