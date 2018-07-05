/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_md5.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ulliwy <Ulliwy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 14:49:35 by iprokofy          #+#    #+#             */
/*   Updated: 2018/07/05 14:45:38 by Ulliwy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MD5_H
# define FT_MD5_H

extern const int g_md5_s[];
extern const int g_md5_K[];

int			md5_prep(int argc, char **argv);
void		hash_open_err(char *name, char *func_name, int name_len);

typedef struct		s_md5
{
	int				q;
	int				r;
	//int				s;
	int 			p;
	char			*filename;
	unsigned char	*str;
	ssize_t			str_len;
	unsigned char	*input;
	ssize_t			input_size;
}					t_md5;

typedef struct s_md5_buf
{
	uint32_t a;
	uint32_t b;
	uint32_t c;
	uint32_t d;
}				t_md5_buf;

#endif
