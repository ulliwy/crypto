/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_md5.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iprokofy <iprokofy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 14:49:35 by iprokofy          #+#    #+#             */
/*   Updated: 2018/04/18 13:47:14 by iprokofy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_MD5_H
# define FT_SSL_MD5_H

extern const int g_md5_s[];
extern const int g_md5_K[];

int			md5_prep(int argc, char **argv);

typedef struct		s_md5
{
	int				q;
	int				r;
	int				s;
	int 			p;
	char			*filename;
	unsigned char	*input;
	ssize_t			in_size;
}					t_md5;

typedef struct s_md5_buf
{
	uint32_t a;
	uint32_t b;
	uint32_t c;
	uint32_t d;
}				t_md5_buf;

#endif
