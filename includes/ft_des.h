/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_des.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iprokofy <iprokofy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/09 11:01:42 by iprokofy          #+#    #+#             */
/*   Updated: 2018/07/09 11:51:25 by iprokofy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DES_H
#define FT_DES_H

#include <unistd.h>

#define ECB 0
#define CBC 1
#define ECB3 2
#define CBC3 3

extern	unsigned char	g_pc1[];
extern	unsigned char	g_pc2[];
extern	unsigned char	g_shifts[];
extern	unsigned char	g_ip[];
extern	unsigned char	g_ebit[];
extern	unsigned char	g_s1[];
extern	unsigned char	g_s2[];
extern	unsigned char	g_s3[];
extern	unsigned char	g_s4[];
extern	unsigned char	g_s5[];
extern	unsigned char	g_s6[];
extern	unsigned char	g_s7[];
extern	unsigned char	g_s8[];
extern	unsigned char	*g_ss[];
extern	unsigned char	g_p[];
extern	unsigned char	g_ip_1[];

typedef struct			s_opt
{
	int					d;
	int					a;
	int					iv;
	unsigned long		v;
	unsigned long		prev;
	char				*entered_key;
	char				*entered_iv;
	char				*input_file;
	char				*output_file;
	unsigned char		*in;
	unsigned char		*out;
	int					fd;
	int 				mode[4];
	unsigned long		keys[3];
}						t_opt;

void					opts_init(t_opt *opts);
char					giv(char c);

void					b64(t_opt *opts);
void					b64_encode(t_opt *opts, ssize_t r);
unsigned char			*b64_decode(unsigned char *in, ssize_t *r);

int						get_iv(t_opt *opts, char *str);

void					des_prep(t_opt opts);
void					des_ecb_encode(ssize_t size, t_opt opts);
unsigned long			des_encryption(unsigned long msg,
							unsigned long keys[16], t_opt opts, int i);
void					des_ecb_decode(ssize_t size, t_opt opts);
unsigned long			des_decryption(unsigned long msg,
							unsigned long keys[16], t_opt opts, int i);

unsigned long			reverse_bits(unsigned long msg);
void					pad(unsigned char *in, ssize_t size);
void					permut_c0d0(unsigned long *c0, unsigned long *d0,
							unsigned long keys[16]);


void					key_gen(unsigned long (*keys)[3][16], t_opt *opts);
int						get_key(t_opt *opts);
int						get_keys3(t_opt *opts);

unsigned long			ff(unsigned long r, unsigned long k);

#endif