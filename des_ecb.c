/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_ecb.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ulliwy <Ulliwy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 12:46:00 by iprokofy          #+#    #+#             */
/*   Updated: 2018/03/22 00:23:09 by Ulliwy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include <stdio.h>

int		put_key_err()
{
	ft_putstr("non-hex digit\n");
	ft_putstr("invalid hex key value\n");
	return (0);
}

int get_keys3(t_opt *opts)
{
	int		i;
	int		k;
	char	c;

	i = 0;
	k = 0;
	//printf("%lu %lu %lu\n", opts->keys[0], opts->keys[1], opts->keys[2]);
	while (opts->entered_key[i] && opts->entered_key[i] != '\n' && i < 48)
	{
		c = ft_tolower(opts->entered_key[i]);
		if (!((c >= 'a' && c <= 'f') || (c >= '0' && c <= '9')))
			return (put_key_err());
		if (c >= 'a' && c <= 'f')
			c = c - 87;
		else
			c = c - '0';
		opts->keys[k] = opts->keys[k] * 16 + c;
		i++;
		if (i && (i % 16 == 0))
			k++;
	}
	// if (i && (i % 16 == 0))
	// 	k++;
	while (i < 48)
	{
		opts->keys[k] = opts->keys[k] * 16;
		i++;
		if (i && (i % 16 == 0))
			k++;
	}
	//printf("%lu %lu %lu\n", opts->keys[0], opts->keys[1], opts->keys[2]);
	return (1);
}

int		get_key(t_opt *opts)
{
	int		len;
	int		i;
	char	c;

	i = 0;
	len = ft_strlen(opts->entered_key);

	if (opts->entered_key[len - 1] == '\n')
		len--;
	while (i < len && i < 16)
	{
		c = ft_tolower(opts->entered_key[i]);
		if (!((c >= 'a' && c <= 'f') || (c >= '0' && c <= '9')))
			return (put_key_err());
		if (c >= 'a' && c <= 'f')
			c = c - 87;
		else
			c = c - '0';
		opts->keys[0] = opts->keys[0] * 16 + c;
		i++;
	}
	while (i < 16)
	{
		opts->keys[0] = opts->keys[0] * 16;
		i++;
	}
	//printf("%lX\n", opts->main_key);
	return (1);
}

unsigned long	permut_pc2(unsigned long c0, unsigned long d0)
{
	unsigned long	key;
	int				i;

	i = 0;
	key = 0;
	while (i < 48)
	{
		key = key | (((1UL << (56 - g_pc2[i])) & (c0 | d0)) ? 1UL << (47 - i) : 0);
		i++;
	}
	return (key);
}

void	permut_c0d0(unsigned long *c0, unsigned long *d0, unsigned long	keys[16])
{
	int i;
	unsigned long	cl;
	unsigned long	cr;
	unsigned long	dl;
	unsigned long	dr;

	i = 0;
	while (i < 16)
	{
		cr = *c0 >> (28 - g_shifts[i]);
		cl = *c0 << g_shifts[i];
		*c0 = (cl | cr) & ((1UL << 56) - (1UL << 28));
		dr = *d0 >> (28 - g_shifts[i]);
		dl = *d0 << g_shifts[i];
		*d0 = (dl | dr) & ((1UL << 28) - 1UL);
		keys[i] = permut_pc2(*c0, *d0);
		i++;
	}
}

void	create_subkeys(unsigned long k, unsigned long	keys[16])
{
	unsigned long	k_plus;
	unsigned long	c0;
	unsigned long	d0;
	int				i;

	i = 0;
	k_plus = 0;
	while (i < 56)
	{
		k_plus = k_plus | ((1UL << (64 - g_pc1[i])) & k ? 1UL << (55 - i) : 0);
		i++;
	}
	c0 = ((1UL << 56) - (1UL << 28)) & k_plus;
	d0 = ((1UL << 28) - 1UL) & k_plus;
	permut_c0d0(&c0, &d0, keys);
}

static inline uint32_t rotl32 (uint32_t x, unsigned int y)
{
  return (x << y) | (x >> (32 - y));
}

static inline uint32_t rotr32 (uint32_t x, unsigned int y)
{
  return (x >> y) | (x << (32 - y));
}

unsigned long	ff(unsigned long r, unsigned long k)
{
	unsigned long	er;
	unsigned long	result;
	int 			i;

	i = 0;
	er = 0;
	result = 0;

	// while (i < 48)
	// {
	// 	er = er | ((1UL << (32 - g_ebit[i])) & r ? 1UL << (47 - i) : 0);
	// 	i++;
	// }

	er = (rotl32(r, 1) & 0x3f)
	  | ((unsigned long)(r & 0x000001f8) << 3)
	  | ((unsigned long)(r & 0x00001f80) << 5)
	  | ((unsigned long)(r & 0x0001f800) << 7)
	  | ((unsigned long)(r & 0x001f8000) << 9)
	  | ((unsigned long)(r & 0x01f80000) << 11)
	  | ((unsigned long)(r & 0x1f800000) << 13)
	  | ((unsigned long)(rotr32(r, 1) & 0xFC000000) << 16);

	er = er ^ k;
	i = 0;
	unsigned long p4 = 0;
	
	while (i < 8)
	{
		unsigned long p1 = (er >> ((7 - i) * 6)) & 63;
		unsigned long p2 = (1 & p1) | ((p1 >> 4) & 2);
		unsigned long p3 = (p1 >> 1) & 15;
		p4 = (p4 << 4) | (g_ss[i][p2 * 16 + p3]);
		i++;
	}
	//int j = 0;
	unsigned int x = p4;
	//#pragma clang loop vectorize(enable)
	//while (j < 32)
	//{
	//	x = x | (((1UL << (32 - g_p[j])) & p4 ? 1UL : 0) << (31 - j));
	//	j++;
	//}
	
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

unsigned long	des_decryption(unsigned long msg, unsigned long keys[16], t_opt opts, int i)
{
	unsigned long	temp;
	int 			j;
	unsigned long	l[17];
	unsigned long	r[17];

	msg = reverse_bits(msg);
	temp = 0;
	j = 0;
	while (j < 64)
	{
		temp = temp | ((msg & 1UL) << (64 - g_ip_1[63 - j]));
		msg = msg >> 1;
		j++;
	}
	
	r[16] = temp >> 32;
	l[16] = temp & ((1UL << 32) - 1UL);
	j = 16;
	while (j >= 1)
	{
		l[j - 1] = r[j] ^ ff(l[j], keys[j - 1]);
		r[j - 1] = l[j];
		j--;
	}
	l[0] = (l[0] << 32) | r[0];
	j = 0;
	temp = 0;
	while (j < 64)
	{
		temp = temp | ((l[0] & 1UL) << (64 - g_ip[63 - j]));
		l[0] = l[0] >> 1;
		j++;
	}
	if (!i && opts.cmd->cbc)
		temp = temp ^ opts.v;
	if (i > 0 && opts.cmd->cbc)
		temp = temp ^ reverse_bits(opts.prev);
	//printf("val: %d\n", val);
	//temp = reverse_bits(temp);
	//(*msg)[i] = temp;
	//write(fd, &temp, sizeof(temp) - (i == size / 8 - 1 ? val : 0));
	return (temp);
}

unsigned long	des_encryption(unsigned long msg, unsigned long keys[16], t_opt opts, int i)
{
	unsigned long	temp;
	int 			j;
	unsigned long	l[17];
	unsigned long	r[17];

	msg = reverse_bits(msg);
	if (!i && opts.cmd->cbc)
		msg = msg ^ opts.v; 
	if (i > 0 && opts.cmd->cbc)
		msg = reverse_bits(opts.prev) ^ msg;
	temp = 0;
	j = 0;
	//initial permutation
	while (j < 64)
	{
		temp = temp | (((1UL << (64 - g_ip[j])) & msg) ? 1UL << (63 - j) : 0);
		j++;
	}
	l[0] = temp >> 32;
	r[0] = temp & ((1UL << 32) - 1UL);
	j = 1;
	while (j <= 16)
	{
		l[j] = r[j - 1];
		r[j] = l[j - 1] ^ ff(r[j - 1], keys[j - 1]);
		j++;
		
	}

	r[16] = (r[16] << 32) | l[16];
	j = 0;
	temp = 0;
	while (j < 64)
	{
		temp = temp | (((1UL << (64 - g_ip_1[j])) & r[16]) ? 1UL << (63 - j) : 0);
		j++;
	}
	msg = reverse_bits(temp);
	return (msg);
}

void	des_ecb_decode(unsigned char *in, int fd, ssize_t size, t_opt opts)
{
	unsigned long	keys[3][16];
	unsigned long	*msg;
	int 			i;
	unsigned long temp;
	unsigned long	*res;

	if (opts.cmd->ecb3 || opts.cmd->cbc3)
	{
		create_subkeys(opts.keys[0], keys[0]);
		create_subkeys(opts.keys[1], keys[1]);
		create_subkeys(opts.keys[2], keys[2]);
	} else
		create_subkeys(opts.keys[0], keys[0]);
	if (opts.a)
		msg = (unsigned long *)b64_decode(in, &size);
	else
		msg = (unsigned long *)in;
	res = (unsigned long *)ft_memalloc(size);
	i = 0;

	int val;
	while (i < size / 8)
	{
		res[i] = msg[i];
		if (i > 0)
			opts.prev = msg[i - 1];
		if (opts.cmd->ecb3 || opts.cmd->cbc3)
		{
			temp = des_decryption(res[i], keys[2], opts, i);
			temp = reverse_bits(temp);
		 	res[i] = des_encryption(temp, keys[1], opts, i);
		}
		temp = des_decryption(res[i], keys[0], opts, i);
		val = temp & 255;
		temp = reverse_bits(temp);
		res[i] = temp;
		i++;
	}
	write(fd, res, sizeof(temp) * i - (i - 1 == size / 8 - 1 ? val : 0));
	free(res);
	if (opts.a)
		free(msg);
}


void	des_ecb_encode(unsigned char *in, int fd, ssize_t size, t_opt opts)
{
	unsigned long	keys[3][16];
	unsigned long	*msg;
	unsigned long	temp;
	int 			i;

	pad(in, size);
	if (opts.cmd->ecb3 || opts.cmd->cbc3)
	{
		create_subkeys(opts.keys[0], keys[0]);
		create_subkeys(opts.keys[1], keys[1]);
		create_subkeys(opts.keys[2], keys[2]);
	} else
		create_subkeys(opts.keys[0], keys[0]);
	msg = (unsigned long *)in;
	i = 0;
	while (i < size / 8 + 1)
	{
		if (i > 0)
			opts.prev = msg[i - 1];
		msg[i] = des_encryption(msg[i], keys[0], opts, i);
		if (opts.cmd->ecb3 || opts.cmd->cbc3)
		{
			temp = des_decryption(msg[i], keys[1], opts, i);
			temp = reverse_bits(temp);
			msg[i] = temp;
			msg[i] = des_encryption(msg[i], keys[2], opts, i);
		}
		i++;
	}
	in = (unsigned char *)msg;
	opts.in = in;
	if (opts.a)
		b64_encode(&opts, (size / 8 + 1) * sizeof(unsigned long));
	else
		write(fd, msg, (size / 8 + 1) * sizeof(unsigned long));
}

void	des_ecb(t_opt *opts)
{
	char	*input;
	ssize_t r;

	if (!opts->input_file) {
		input = get_from_fd(0, &r);
		printf("->>>>>%s\n", input);
	}
	else
	{
		if ((opts->fd = open(opts->input_file, O_RDONLY)) == -1)
		{
			put_open_err(opts->input_file);
			return ;
		}
	 	input = get_from_fd(opts->fd, &r);
	 	close(opts->fd);
	}
	if (!opts->output_file) {
		opts->fd = 1;
	}
	else if ((opts->fd = open(opts->output_file, O_CREAT | O_WRONLY | O_APPEND | O_TRUNC, 0644)) == -1)
	{
		put_open_err(opts->output_file);
		return ;
	}
	
	if (opts->cmd->cbc3)
		opts->cmd->cbc = 1;
	if (opts->d)
		des_ecb_decode((unsigned char *)input, opts->fd, r, *opts);
	else
		des_ecb_encode((unsigned char *)input, opts->fd, r, *opts);
	close(opts->fd);
	free(input);
}

void	des_prep(t_opt opts)
{
	int		allocated;

	allocated = 0;
	if (!opts.entered_key)
	{
		opts.entered_key = (char *)ft_memalloc(100);
		ft_putstr("enter des key in hex: ");
		read(1, opts.entered_key, 100);
		allocated = 1;
	}
	if (opts.cmd->ecb3 || opts.cmd->cbc3)
	{
		if (!get_keys3(&opts))
			return ;
	}
	else if(!get_key(&opts))
		return ; 
	des_ecb(&opts);
	if (allocated)
		free(opts.entered_key);
}
