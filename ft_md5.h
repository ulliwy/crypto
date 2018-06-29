/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_md5.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ulliwy <Ulliwy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 14:49:35 by iprokofy          #+#    #+#             */
/*   Updated: 2018/06/28 21:12:52 by Ulliwy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MD5_H
# define FT_MD5_H

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
	unsigned char	*str;
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
