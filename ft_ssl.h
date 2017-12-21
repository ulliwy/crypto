/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iprokofy <iprokofy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 12:47:44 by Ulliwy            #+#    #+#             */
/*   Updated: 2017/12/20 14:42:09 by iprokofy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include "libft/libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

# include <stdio.h>

# define BUFF_SIZE	512

extern 	unsigned char	g_pc1[];
extern	unsigned char	g_pc2[];
extern	unsigned char	g_shifts[];
extern	unsigned char	g_ip[];

typedef struct			s_cmd
{
	int					b64;
	int 				ecb;
}						t_cmd;

typedef struct			s_opt
{
	int					e;
	int					d;
	unsigned long		main_key;
	char				*entered_key;
	char				*input_file;
	char				*output_file;
}						t_opt;

void					b64(t_opt opts);
void					des_prep(t_opt opts);

char					*get_from_fd(int fd, ssize_t *r);
void					print_bits(unsigned long octet, int sep);

void					put_open_err(char *name);

#endif