/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ulliwy <Ulliwy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 11:23:32 by iprokofy          #+#    #+#             */
/*   Updated: 2017/12/14 17:13:16 by Ulliwy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

char 	giv(char c)
{
	if (c >= 'A' && c<= 'Z')
		return (c - 65);
	else if (c >= 'a' && c <= 'z')
		return (c - 71);
	else if (c >= '0' && c <= '9')
		return (c + 4);
	else if (c == '+')
		return (62);
	else
		return (63);
}

void	*put_stream_err()
{
	ft_putstr("Invalid character in input stream.");
	return (NULL);
}

char	*remove_spaces(char *in)
{
	int 	i;
	int 	j;

	i = 0;
	j = 0;
	while (in[i])
	{
		if ((in[i] >= 'A' && in[i] <='Z') || (in[i] >= 'a' && in[i] <='z') ||
			(in[i] >= '0' && in[i] <='9') || in[i] == '+' || in[i] == '/' ||
			in[i] == '=')
		{
			in[j] = in[i];
			i++;
			j++;
		}
		else if (in[i] == ' ' || in[i] == '\n' || in[i] == '\t')
			i++;
		else
			return (put_stream_err());
	}
	in[j] = '\0';
	return (in);
}

void	b64_decode(char *in, int fd)
{
	in = remove_spaces(in);
	while (*in && *in != '=')
	{
		ft_putchar_fd((giv(in[0]) << 2) | ((giv(in[1]) == -1 ? 0 : (giv(in[1])) >> 4)), fd);
		if (in[2] != '=')
			ft_putchar_fd(((giv(in[1]) & 15) << 4) | ((giv(in[2]) == -1 ? 0 : giv(in[2])) >> 2), fd);
		if (in[3] != '=')
			ft_putchar_fd(((giv(in[2]) & 3) << 6) | ((giv(in[3]) == -1 ? 0 : giv(in[3])) & 63), fd);
		in += 4;
	}
}

void	b64_encode(unsigned char *in, int fd, ssize_t r)
{
	char	*b64;
	int 	b;
	int 	i;

	b = 0;
	i = 0;
	b64 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	while (i < r)
	{
		ft_putchar_fd(b64[(int)(in[i] >> 2)], fd);
		i++;
		if (i < r)
			ft_putchar_fd(b64[(int)(((in[i - 1] & 3) << 4) | ((in[i] & 240) >> 4))], fd);
		else
			ft_putchar_fd(b64[(int)((in[i - 1] & 3) << 4)], fd);
		i++;
		if (i == r)
			ft_putchar_fd(b64[(int)(((in[i - 1] & 15) << 2))], fd);
		else if (i < r)
			ft_putchar_fd(b64[(int)(((in[i - 1] & 15) << 2) | ((in[i] & 192) >> 6))], fd);
		else
		{
			ft_putchar_fd('=', fd);
			b = 1;
		}
		if (i < r)
			ft_putchar_fd(b64[(int)(in[i] & 63)], fd);
		else
		{
			ft_putchar_fd('=', fd);
			b = 1;
		}
		if (b)
			break;
		i++;
	}
	ft_putchar_fd('\n', fd);
}

void	put_open_err(char *name)
{
	char *err_msg;
	int len;

	len = ft_strlen(name);
	err_msg = (char *)ft_memalloc(len + 18);
	ft_strcpy(err_msg, "Unable to open \'");
	ft_strcpy(err_msg + 16, name);
	err_msg[16 + len] = '\'';
	perror(err_msg);
	free(err_msg);
}

void	b64(t_opt opts)
{
	char	*input;
	int 	fd;
	ssize_t r;

	if (!opts.input_file)
		input = get_from_fd(0, &r);
	else
	{
		if ((fd = open(opts.input_file, O_RDONLY)) == -1)
		{
			put_open_err(opts.input_file);
			return ;
		}
	 	input = get_from_fd(fd, &r);
	 	close(fd);
	}
	if (!opts.output_file)
		fd = 1;
	else
	{
		if ((fd = open(opts.output_file, O_CREAT | O_WRONLY | O_TRUNC, 0644)) == -1)
		{
			put_open_err(opts.output_file);
			return ;
		}
	}
	if (opts.d)
		b64_decode(input, fd);
	else
		b64_encode((unsigned char *)input, fd, r);
	close(fd);
	free(input);
}
