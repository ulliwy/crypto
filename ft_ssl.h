/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ulliwy <Ulliwy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 12:47:44 by Ulliwy            #+#    #+#             */
/*   Updated: 2018/03/21 23:27:50 by Ulliwy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include "libft/libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>

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
}						t_cmd;

typedef struct			s_opt
{
	int					d;
	int					a;
	int					iv;
	unsigned long		v;
	unsigned long		prev;
	char				*entered_key;
	char				*input_file;
	char				*output_file;
	unsigned char		*in;
	unsigned char		*out;
	int					fd;
	t_cmd				*cmd;
	unsigned long		keys[3];
}						t_opt;

void					b64(t_opt *opts);
void					b64_encode(t_opt *opts, ssize_t r);
unsigned char			*b64_decode(unsigned char *in, ssize_t *r);
void					des_prep(t_opt opts);
unsigned long			reverse_bits(unsigned long msg);
void					pad(unsigned char *in, ssize_t size);

char					*get_from_fd(int fd, ssize_t *r);
void					print_bits(unsigned long octet, int sep);

void					put_open_err(char *name);

#endif
