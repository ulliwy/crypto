/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hash.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ulliwy <Ulliwy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 16:37:43 by Ulliwy            #+#    #+#             */
/*   Updated: 2018/07/16 16:49:34 by Ulliwy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_hash.h>
#include "libft.h"

void	print_hex(uint32_t c)
{
	char	base[17] = "0123456789abcdef";

	ft_putchar(base[c / 16]);
	ft_putchar(base[c % 16]);
}

void print_hex64(uint64_t *buffer, int buf_size)
{
	int i;

	i = 0;
	while (i < buf_size)
	{
		print_hex((buffer[i] & 0xFF00000000000000) >> 8 * 7);
		print_hex((buffer[i] & 0xFF000000000000) >> 8 * 6);
		print_hex((buffer[i] & 0xFF0000000000) >> 8 * 5);
		print_hex((buffer[i] & 0xFF00000000) >> 8 * 4);
		print_hex((buffer[i] & 0xFF000000) >> 8 * 3);
		print_hex((buffer[i] & 0xFF0000) >> 8 * 2);
		print_hex((buffer[i] & 0xFF00) >> 8);
		print_hex(buffer[i] & 0xFF);
		i++;
	}
}

void print_hex32(uint32_t *buffer, int buf_size)
{
	int i;

	i = 0;
	while (i < buf_size)
	{
		print_hex((buffer[i] & 0xFF000000) >> 8 * 3);
		print_hex((buffer[i] & 0xFF0000) >> 8 * 2);
		print_hex((buffer[i] & 0xFF00) >> 8);
		print_hex(buffer[i] & 0xFF);
		i++;
	}
}

void	print_hash(void *buffer, int buf_size, char *name, t_hash *opts)
{
	if (opts->pp)
	{
		write(1, opts->input, opts->input_size);
		opts->pp = 0;
	}
	if (opts->str && !opts->q && !opts->r)
	{
		write(1, name, ft_strlen(name));
		write(1, " (\"", 3);
		write(1, opts->str, opts->str_len);
		write(1, "\") = ", 5);
	}
	else if (!opts->q && opts->filename && !opts->r)
	{
		write(1, name, ft_strlen(name));
		write(1, " (", 2);
		write(1, opts->filename, ft_strlen(opts->filename));
		write(1, ") = ", 4);
	}
	if (opts->id == SHA512)
		print_hex64(buffer, buf_size);
	else
		print_hex32(buffer, buf_size);
	if (opts->r && opts->str && !opts->q)
	{
		write(1, " \"", 2);
		write(1, opts->str, opts->str_len);
		write(1, "\"", 1);
	}
	else if (!opts->q && opts->filename && opts->r)
	{
		write(1, " ", 1);
		write(1, opts->filename, ft_strlen(opts->filename));
	}

	write(1, "\n", 1);
}
