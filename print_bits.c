/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_bits.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iprokofy <iprokofy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 14:28:05 by iprokofy          #+#    #+#             */
/*   Updated: 2017/12/14 14:43:33 by iprokofy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	wrapper(unsigned long octet, int i)
{
	if (i > 63)
		return ;
	wrapper(octet / 2, i + 1);
	ft_putchar(octet % 2 + '0');
	if (i && i % 4 == 0)
		ft_putchar(' ');
}

void	print_bits(unsigned long octet)
{
	int		i;

	i = 0;
	wrapper(octet, i);
}