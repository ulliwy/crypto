/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buff_read.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ulliwy <Ulliwy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 14:07:40 by iprokofy          #+#    #+#             */
/*   Updated: 2018/03/22 11:42:59 by Ulliwy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

char	*get_from_fd(int fd, ssize_t *r)
{
	char		*input;
	char		*new;
	ssize_t		rd;
	ssize_t		available;

	available = BUFF_SIZE;
	if (!(input = (char *)ft_memalloc(available)))
		return (NULL);
	*r = 0;
	while ((rd = read(fd, input + *r, available)))
	{
		if (rd == -1)
			return (NULL);
		available -= rd;
		*r += rd;
		if (!available)
		{
			new = (char *)ft_memalloc(BUFF_SIZE + (*r));
			ft_memcpy(new, input, *r);
			free(input);
			input = new;
			available = BUFF_SIZE;
		}
	}
	return (input);
}
