/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hash.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iprokofy <iprokofy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 14:49:35 by iprokofy          #+#    #+#             */
/*   Updated: 2018/07/20 13:23:50 by iprokofy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_HASH_H
# define FT_HASH_H

# include <sys/types.h>
# include <stdint.h>

# define MD5 		0
# define SHA256 	1
# define SHA512		2

extern const int g_md5_s[];
extern const int g_md5_k[];

extern const uint32_t g_sha256_k[];
extern const uint64_t g_sha512_k[];

typedef struct		s_hash
{
	int				id;
	int				q;
	int				r;
	int				s;
	int				p;
	int				pp;
	char			*filename;
	unsigned char	*str;
	ssize_t			str_len;
	unsigned char	*input;
	ssize_t			input_size;
	unsigned char	*from_file;
	ssize_t			file_size;
}					t_hash;

typedef struct		s_md5_buf
{
	uint32_t		a;
	uint32_t		b;
	uint32_t		c;
	uint32_t		d;
}					t_md5_buf;

typedef struct		s_sha256_buf
{
	uint32_t		a;
	uint32_t		b;
	uint32_t		c;
	uint32_t		d;
	uint32_t		e;
	uint32_t		f;
	uint32_t		g;
	uint32_t		h;
}					t_sha256_buf;

typedef struct		s_sha512_buf
{
	uint64_t		a;
	uint64_t		b;
	uint64_t		c;
	uint64_t		d;
	uint64_t		e;
	uint64_t		f;
	uint64_t		g;
	uint64_t		h;
}					t_sha512_buf;

void				hash_open_err(char *name, char *func_name, int name_len);

void				md5(unsigned char *msg, ssize_t size, t_hash *opts);

void				sha256(unsigned char *msg, ssize_t size, t_hash *opts);
void				sha512(unsigned char *msg, ssize_t size, t_hash *opts);

unsigned char		*sha512_pad_msg(unsigned char *msg, ssize_t *size);
unsigned char		*sha256_pad_msg(unsigned char *msg, ssize_t *size);
unsigned char		*md5_pad_msg(unsigned char *msg, ssize_t *size);

void				print_bits(unsigned char octet, int sep);
void				print_hash(void *buffer, int buf_size, char *name,
								t_hash *opts);

uint64_t			right_rotate_64(uint64_t x, int c);
uint32_t			right_rotate(uint32_t x, int c);
uint32_t			left_rotate(uint32_t x, int c);

#endif
