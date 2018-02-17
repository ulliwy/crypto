/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iprokofy <iprokofy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 11:23:32 by iprokofy          #+#    #+#             */
/*   Updated: 2018/02/16 15:59:53 by iprokofy         ###   ########.fr       */
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
	ft_putstr("Invalid character in input stream.\n");
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
		else if (in[i] == ' ' || in[i] == '\n' || in[i] == '\t' || in[i] == 13) {
			i++;
		}
		else
			return (put_stream_err());
	}
	in[j] = '\0';
	return (in);
}

void	b64_decode(char *in, int fd)
{
	in = remove_spaces(in);
	while (in && *in && *in != '=')
	{

		ft_putchar_fd((giv(in[0]) << 2) | ((giv(in[1]) == -1 ? 0 : (giv(in[1])) >> 4)), fd);
		if (in[2] != '=')
			ft_putchar_fd(((giv(in[1]) & 15) << 4) | ((giv(in[2]) == -1 ? 0 : giv(in[2])) >> 2), fd);
		if (in[3] != '=')
			ft_putchar_fd(((giv(in[2]) & 3) << 6) | ((giv(in[3]) == -1 ? 0 : giv(in[3])) & 63), fd);
		in += 4;
	}
}

void	b64_encode(t_opt *opts, ssize_t r)
{
	char	*b64;
	int 	b;
	int 	i;
	unsigned char 	*in;

	b = 0;
	i = 0;

	in = opts->in;
	b64 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	opts->out = (unsigned char *)ft_memalloc(((r / 3) + 1) * 4 + 2);
	//start = opts->out;
	while (i < r)
	{
		ft_putchar_fd(b64[(int)(opts->in[i] >> 2)], opts->fd);
		//*(opts->out) = b64[(int)(opts->in[i] >> 2)];
		//opts->out++;
		i++;
		if (i < r)
		{
			ft_putchar_fd(b64[(int)(((in[i - 1] & 3) << 4) | ((in[i] & 240) >> 4))], opts->fd);
			//*opts->out = b64[(int)(((opts->in[i - 1] & 3) << 4) | ((opts->in[i] & 240) >> 4))];
		}
		else
			//*opts->out = b64[(int)((opts->in[i - 1] & 3) << 4)];
			ft_putchar_fd(b64[(int)((in[i - 1] & 3) << 4)], opts->fd);
		i++;
		//opts->out++;
		if (i == r)
			//*opts->out = b64[(int)(((opts->in[i - 1] & 15) << 2))];
			ft_putchar_fd(b64[(int)(((in[i - 1] & 15) << 2))], opts->fd);
		else if (i < r)
			//*opts->out = b64[(int)(((opts->in[i - 1] & 15) << 2) | ((opts->in[i] & 192) >> 6))];
			ft_putchar_fd(b64[(int)(((in[i - 1] & 15) << 2) | ((in[i] & 192) >> 6))], opts->fd);
		else
		{
			//*opts->out = '=';
			ft_putchar_fd('=', opts->fd);
			b = 1;
		}
		//opts->out++;
		if (i < r)
			//*opts->out = b64[(int)(opts->in[i] & 63)];
			ft_putchar_fd(b64[(int)(in[i] & 63)], opts->fd);
		else
		{
			//*opts->out = '=';
			ft_putchar_fd('=', opts->fd);
			b = 1;
		}
		//opts->out++;
		if (b)
			break;
		i++;
	}
	ft_putchar_fd('\n', opts->fd);
	// *opts->out++ = '\n';
	// *opts->out = '\0';
	// ft_putstr_fd((char *)start, opts->fd);
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

void	b64(t_opt *opts)
{
	ssize_t r;

	if (!opts->input_file)
		opts->in = (unsigned char *)get_from_fd(0, &r);
	else
	{
		if ((opts->fd = open(opts->input_file, O_RDONLY)) == -1)
		{
			put_open_err(opts->input_file);
			return ;
		}
	 	opts->in = (unsigned char *)get_from_fd(opts->fd, &r);
	 	close(opts->fd);
	}
	if (!opts->output_file)
		opts->fd = 1;
	else
	{
		if ((opts->fd = open(opts->output_file, O_CREAT | O_WRONLY | O_TRUNC, 0644)) == -1)
		{
			put_open_err(opts->output_file);
			return ;
		}
	}
	if (opts->d)
		b64_decode((char *)opts->in, opts->fd);
	else
		b64_encode(opts, r);
	close(opts->fd);
	free(opts->in);
}
