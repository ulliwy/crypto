/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_bits.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iprokofy <iprokofy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 14:28:05 by iprokofy          #+#    #+#             */
/*   Updated: 2018/07/19 10:34:16 by iprokofy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	wrapper(unsigned char octet, int i, int sep)
{
	if (i > 7)
		return ;
	wrapper(octet / 2, i + 1, sep);
	ft_putchar(octet % 2 + '0');
	if (i && i % sep == 0)
		ft_putchar(' ');
}

void	print_bits(unsigned char octet, int sep)
{
	int		i;

	i = 0;
	wrapper(octet, i, sep);
}

void	wrapper_2(unsigned long octet, int i, int sep)
{
	if (i > 63)
		return ;
	wrapper_2(octet / 2, i + 1, sep);
	ft_putchar(octet % 2 + '0');
	if (i && i % sep == 0)
		ft_putchar(' ');
}

void	print_bits_long(unsigned long octet, int sep)
{
	int		i;

	i = 0;
	wrapper_2(octet, i, sep);
}
