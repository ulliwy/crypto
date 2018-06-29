/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bit_permut.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ulliwy <Ulliwy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 15:44:28 by iprokofy          #+#    #+#             */
/*   Updated: 2018/06/28 17:27:04 by Ulliwy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ssl.h"

static inline uint32_t		rotl32(uint32_t x, unsigned int y)
{
	return ((x << y) | (x >> (32 - y)));
}

static inline uint32_t		rotr32(uint32_t x, unsigned int y)
{
	return ((x >> y) | (x << (32 - y)));
}

static inline unsigned int	get_p4(unsigned long p4)
{
	unsigned int x;

	x = p4;
	x = ((x & 0x00000004) << 3)
		| ((x & 0x00004000) << 4)
		| rotl32(x & 0x12020120, 5)
		| ((x & 0x00100000) << 6)
		| ((x & 0x00008000) << 9)
		| ((x & 0x04000000) >> 22)
		| ((x & 0x00000001) << 11)
		| rotl32(x & 0x20000200, 12)
		| ((x & 0x00200000) >> 19)
		| ((x & 0x00000040) << 14)
		| ((x & 0x00010000) << 15)
		| ((x & 0x00000002) << 16)
		| rotl32(x & 0x40801800, 17)
		| ((x & 0x00080000) >> 13)
		| ((x & 0x00000010) << 21)
		| ((x & 0x01000000) >> 10)
		| rotl32(x & 0x88000008, 24)
		| ((x & 0x00000480) >> 7)
		| ((x & 0x00442000) >> 6);
	return (x);
}

unsigned long				ff(unsigned long r, unsigned long k)
{
	unsigned long	er;
	int				i;
	unsigned long	p1;
	unsigned long	p2;
	unsigned long	p4;

	er = ((rotl32(r, 1) & 0x3f)
		| ((unsigned long)(r & 0x000001f8) << 3)
		| ((unsigned long)(r & 0x00001f80) << 5)
		| ((unsigned long)(r & 0x0001f800) << 7)
		| ((unsigned long)(r & 0x001f8000) << 9)
		| ((unsigned long)(r & 0x01f80000) << 11)
		| ((unsigned long)(r & 0x1f800000) << 13)
		| ((unsigned long)(rotr32(r, 1) & 0xFC000000) << 16)) ^ k;
	i = 0;
	p4 = 0;
	while (i < 8)
	{
		p1 = (er >> ((7 - i) * 6)) & 63;
		p2 = (1 & p1) | ((p1 >> 4) & 2);
		p4 = (p4 << 4) | (g_ss[i][p2 * 16 + ((p1 >> 1) & 15)]);
		i++;
	}
	return (get_p4(p4));
}
