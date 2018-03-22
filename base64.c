/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ulliwy <Ulliwy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 11:23:32 by iprokofy          #+#    #+#             */
/*   Updated: 2018/03/22 00:44:20 by Ulliwy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

char	giv(char c)
{
	if (c >= 'A' && c <= 'Z')
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

void	*put_stream_err(void)
{
	ft_putstr("Invalid character in input stream.\n");
	return (NULL);
}

unsigned char	*remove_spaces(unsigned char *in, ssize_t *size)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	//printf("AAAAAAAAAAAA{%c}\n", in[0]);
	while ((ssize_t)i < *size)
	{
		if ((in[i] >= 'A' && in[i] <= 'Z') || (in[i] >= 'a' && in[i] <= 'z') ||
			(in[i] >= '0' && in[i] <= '9') || in[i] == '+' || in[i] == '/' ||
			in[i] == '=')
		{
			in[j] = in[i];
			i++;
			j++;
		}
		else if (in[i] == ' ' || in[i] == '\n' || in[i] == '\t' || in[i] == 13)
			i++;
		else
			return (put_stream_err());
	}
	in[j] = '\0';
	*size = j;
	return (in);
}

unsigned char	*b64_decode(unsigned char *in, ssize_t *r)
{
	ssize_t			new_size;
	unsigned char	*temp;
	int				i;

	//printf("%s\n", in);
	in = remove_spaces(in, r);
	new_size = (*r / 4) * 3;
	*r = new_size;
	temp = (unsigned char *)ft_memalloc(new_size + 1);
	temp[new_size] = '\0';
	i = 0;
	while (in && *in && *in != '=')
	{
		temp[i] = (giv(in[0]) << 2) | ((giv(in[1]) == -1 ?
				0 : (giv(in[1])) >> 4));
		if (in[2] != '=')
			temp[i + 1] = ((giv(in[1]) & 15) << 4) |
				((giv(in[2]) == -1 ? 0 : giv(in[2])) >> 2);
		if (in[3] != '=')
			temp[i + 2] = ((giv(in[2]) & 3) << 6) |
				((giv(in[3]) == -1 ? 0 : giv(in[3])) & 63);
		i = i + 3;
		in += 4;
	}
	return (temp);
}

void	b64_encode(t_opt *opts, ssize_t r)
{
	char			*b64;
	int				b;
	int				i;
	int				j;
	unsigned char	*in;

	b = 0;
	i = 0;
	j = 0;
	in = opts->in;
	b64 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	opts->out = (unsigned char *)ft_memalloc(((r / 3) + 1) * 4 + 1 + (((r / 3) + 1) * 4 + 1) / 64 + 1);
	while (i < r)
	{
		opts->out[j++] = b64[(int)(opts->in[i++] >> 2)];
		//i++;
		//j++;
		if (i < r)
			opts->out[j++] = b64[(int)(((in[i - 1] & 3) << 4) | ((in[i] & 240) >> 4))];
		else
			opts->out[j++] = b64[(int)((in[i - 1] & 3) << 4)];
		i++;
		//j++;
		if (i == r)
			opts->out[j] = b64[(int)(((in[i - 1] & 15) << 2))];
		else if (i < r)
			opts->out[j] = b64[(int)(((in[i - 1] & 15) << 2) | ((in[i] & 192) >> 6))];
		else
		{
			opts->out[j] = '=';
			b = 1;
		}
		j++;
		if (i < r)
			opts->out[j] = b64[(int)(opts->in[i] & 63)];
		else
		{
			opts->out[j] = '=';
			b = 1;
		}
		j++;
		if (j && ((j + 1) % 65 == 0) && opts->entered_key)
		{
			opts->out[j] = '\n';
			j++;
		}
		if (b)
			break ;
		i++;
	}
	opts->out[j] = '\n';
	opts->out[j + 1] = '\0';
	write(opts->fd, opts->out, j + 1);
	free(opts->out);
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
			return (put_open_err(opts->input_file));
	 	opts->in = (unsigned char *)get_from_fd(opts->fd, &r);
	 	close(opts->fd);
	}
	if (!opts->output_file)
		opts->fd = 1;
	else if ((opts->fd = open(opts->output_file, O_CREAT | O_WRONLY | O_TRUNC, 0644)) == -1)
		return (put_open_err(opts->output_file));
	if (opts->d)
	{
		unsigned char *decoded = b64_decode(opts->in, &r);
		write(opts->fd, decoded, r);
	}
	else
		b64_encode(opts, r);
	close(opts->fd);
	free(opts->in);
}
