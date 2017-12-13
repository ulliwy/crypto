/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iprokofy <iprokofy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 11:23:32 by iprokofy          #+#    #+#             */
/*   Updated: 2017/12/12 16:30:46 by iprokofy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"


void	b64_decode(char *in)
{
	ft_putstr(in);
}

void	b64_encode(char *in)
{
	char	*b64;

	b64 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	ft_putstr(in);
}

void	b64(t_opt opts)
{
	char	*input;
	int 	fd;

	if (!opts.input_file)
		input = get_from_fd(0);
	else
	{
		fd = open(opts.input_file, O_RDONLY);
	 	input = get_from_fd(fd);
	 	close(fd);
	}
	if (opts.d)
		b64_decode(input);
	else
		b64_encode(input);
	free(input);
	//printf("input buffer: <<%s>>\n", input);
}
