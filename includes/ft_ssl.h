/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ulliwy <Ulliwy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 12:47:44 by Ulliwy            #+#    #+#             */
/*   Updated: 2018/07/09 21:21:48 by Ulliwy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include <sys/types.h>

# define BUFF_SIZE	1024*1024

typedef struct			s_cmd
{
	int					b64;
	int					ecb;
	int					cbc;
	int					ecb3;
	int					cbc3;
	int					hashing;
}						t_cmd;

void					cmd_init(t_cmd *cmd);




char					*get_from_fd(int fd, ssize_t *r);
void					print_bits(unsigned char octet, int sep);
void					print_bits_long(unsigned long octet, int sep);


int						hash_prep(int argc, char **argv, int func_id);

#endif
