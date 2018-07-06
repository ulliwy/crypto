/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ulliwy <Ulliwy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 12:47:44 by Ulliwy            #+#    #+#             */
/*   Updated: 2018/07/06 15:58:49 by Ulliwy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>
# include "libft/libft.h"

# define BUFF_SIZE	1024*1024

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

typedef struct			s_cmd
{
	int					b64;
	int					ecb;
	int					cbc;
	int					ecb3;
	int					cbc3;
	int					hashing;
}						t_cmd;

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
	t_cmd				*cmd;
	unsigned long		keys[3];
}						t_opt;

void					opts_init(t_opt *opts, t_cmd *cmd);
void					cmd_init(t_cmd *cmd);
char					giv(char c);

int						get_key(t_opt *opts);
int						get_keys3(t_opt *opts);
void					permut_c0d0(unsigned long *c0, unsigned long *d0,
							unsigned long keys[16]);
unsigned long			ff(unsigned long r, unsigned long k);
void					key_gen(unsigned long (*keys)[3][16], t_opt *opts);
int						get_iv(t_opt *opts, char *str);

void					b64(t_opt *opts);
void					b64_encode(t_opt *opts, ssize_t r);
unsigned char			*b64_decode(unsigned char *in, ssize_t *r);
void					des_prep(t_opt opts);
unsigned long			reverse_bits(unsigned long msg);
void					pad(unsigned char *in, ssize_t size);

void					des_ecb_encode(ssize_t size, t_opt opts);
unsigned long			des_encryption(unsigned long msg,
							unsigned long keys[16], t_opt opts, int i);
void					des_ecb_decode(ssize_t size, t_opt opts);
unsigned long			des_decryption(unsigned long msg,
							unsigned long keys[16], t_opt opts, int i);

char					*get_from_fd(int fd, ssize_t *r);
void					print_bits(unsigned char octet, int sep);
void					print_bits_long(unsigned long octet, int sep);

void					put_open_err(char *name);
int						err_usage(int type);
int						err_options(char cmd);
int						err_usage_commands(char *cmd);
int						put_iv_err(int type);
void					*put_stream_err(void);
int						put_key_err(void);

int						hash_prep(int argc, char **argv, int func_id);

#endif
