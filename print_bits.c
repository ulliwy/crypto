/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_bits.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iprokofy <iprokofy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 14:28:05 by iprokofy          #+#    #+#             */
/*   Updated: 2018/03/23 13:03:19 by iprokofy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	wrapper(unsigned long octet, int i, int sep)
{
	if (i > 63)
		return ;
	wrapper(octet / 2, i + 1, sep);
	ft_putchar(octet % 2 + '0');
	if (i && i % sep == 0)
		ft_putchar(' ');
}

void	print_bits(unsigned long octet, int sep)
{
	int		i;

	i = 0;
	wrapper(octet, i, sep);
}
