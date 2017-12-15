/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ulliwy <Ulliwy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 12:47:44 by Ulliwy            #+#    #+#             */
/*   Updated: 2017/12/14 16:28:52 by Ulliwy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include "libft/libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

# include <stdio.h>

# define BUFF_SIZE	100

extern unsigned char	g_pc1[];

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

char	*get_from_fd(int fd, ssize_t *r);
void					print_bits(unsigned long octet);

#endif