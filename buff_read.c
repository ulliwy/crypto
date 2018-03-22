/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buff_read.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ulliwy <Ulliwy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 14:07:40 by iprokofy          #+#    #+#             */
/*   Updated: 2018/03/22 00:29:50 by Ulliwy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

char	*get_from_fd(int fd, ssize_t *r)
{
	char		*input;
	char		*new;
	ssize_t		rd;
	int			offset;

	if (!(input = (char *)ft_memalloc(BUFF_SIZE + 9)))
		return (NULL);
	offset = 0;
	*r = 0;
	while ((rd = read(fd, input + *r, BUFF_SIZE)))
	{
		if (rd == -1){
			printf("SECOND\n");
			return (input);
		}
		*r += rd;
		offset++;
		if (rd == BUFF_SIZE)
		{
			new = (char *)ft_memalloc(BUFF_SIZE + offset * BUFF_SIZE + 9);
			ft_memcpy(new, input, offset * BUFF_SIZE);
			free(input);
			input = new;
		}
	}
	printf("func: %s\n", input);
	return (input);
}
