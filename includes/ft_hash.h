/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hash.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ulliwy <Ulliwy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 14:49:35 by iprokofy          #+#    #+#             */
/*   Updated: 2018/07/10 15:45:47 by Ulliwy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_HASH_H
# define FT_HASH_H

# include <sys/types.h>
# include <stdint.h>

extern const int g_md5_s[];
extern const int g_md5_K[];

extern const uint32_t g_sha256_k[];

typedef struct		s_hash
{
	int 			id;
	int				q;
	int				r;
	int				s;
	int 			p;
	int 			pp;
	char			*filename;
	unsigned char	*str;
	ssize_t			str_len;
	unsigned char	*input;
	ssize_t			input_size;
	unsigned char 	*from_file;
	ssize_t 		file_size;
}					t_hash;

typedef struct		s_md5_buf
{
	uint32_t		a;
	uint32_t		b;
	uint32_t		c;
	uint32_t		d;
}					t_md5_buf;

typedef struct 		s_sha256_buf
{
	uint32_t a;
	uint32_t b;
	uint32_t c;
	uint32_t d;
	uint32_t e;
	uint32_t f;
	uint32_t g;
	uint32_t h;
} 					t_sha256_buf;

void				hash_open_err(char *name, char *func_name, int name_len);

void				md5(unsigned char *msg, ssize_t size, t_hash *opts);

void				sha256(unsigned char *msg, ssize_t size, t_hash *opts);

void 				add_size_representation(unsigned char *msg, ssize_t size, ssize_t new_size);

void				print_bits(unsigned char octet, int sep); // to remove
void				print_hash(uint32_t *buffer, int buf_size, char *name, t_hash *opts);

#endif
