/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iprokofy <iprokofy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/20 13:14:20 by iprokofy          #+#    #+#             */
/*   Updated: 2018/07/20 13:24:23 by iprokofy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <inttypes.h>

extern uint64_t	right_rotate_64(uint64_t x, int c)
{
	return (x >> c) | (x << (64 - c));
}

extern uint32_t	right_rotate(uint32_t x, int c)
{
	return (x >> c) | (x << (32 - c));
}

extern uint32_t	left_rotate(uint32_t x, int c)
{
	return (x << c) | (x >> (32 - c));
}
