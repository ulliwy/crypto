/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ulliwy <Ulliwy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 11:23:32 by iprokofy          #+#    #+#             */
/*   Updated: 2018/06/28 17:26:55 by Ulliwy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_des.h"
#include "ft_err.h"
#include "libft.h"
#include "ft_ssl.h"
#include <fcntl.h>

unsigned char	*remove_spaces(unsigned char *in, ssize_t *size)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
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
		else if (in[i] == ' ' || in[i] == '\n' || in[i] == '\t'
				|| in[i] == 13 || in[i] == 3)
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
	unsigned char	*temp;
	int				i;

	in = remove_spaces(in, r);
	*r = (*r / 4) * 3;
	temp = (unsigned char *)ft_memalloc(*r);
	i = 0;
	while (in && *in && *in != '=')
	{
		temp[i] = (giv(in[0]) << 2) | ((giv(in[1]) == -1 ?
				0 : (giv(in[1])) >> 4));
		if (in[2] != '=')
			temp[i + 1] = ((giv(in[1]) & 15) << 4) |
				((giv(in[2]) == -1 ? 0 : giv(in[2])) >> 2);
		else
			(*r)--;
		if (in[3] != '=')
			temp[i + 2] = ((giv(in[2]) & 3) << 6) |
				((giv(in[3]) == -1 ? 0 : giv(in[3])) & 63);
		else
			(*r)--;
		i = i + 3;
		in += 4;
	}
	return (temp);
}

void			b54_encryption(t_opt *opts, int *i, int *j, ssize_t r)
{
	char			*b64;

	b64 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	opts->out[(*j)++] = b64[(int)(opts->in[(*i)++] >> 2)];
	if ((*i) < r)
		opts->out[(*j)++] = b64[(int)(((opts->in[*i - 1] & 3) << 4) |
			((opts->in[*i] & 240) >> 4))];
	else
		opts->out[(*j)++] = b64[(int)((opts->in[*i - 1] & 3) << 4)];
	(*i)++;
	if (*i == r)
		opts->out[*j] = b64[(int)(((opts->in[*i - 1] & 15) << 2))];
	else if (*i < r)
		opts->out[*j] = b64[(int)(((opts->in[*i - 1] & 15) << 2) |
			((opts->in[*i] & 192) >> 6))];
	else
		opts->out[*j] = '=';
	(*j)++;
	if (*i < r)
		opts->out[*j] = b64[(int)(opts->in[*i] & 63)];
	else
		opts->out[*j] = '=';
	(*j)++;
}

void			b64_encode(t_opt *opts, ssize_t r)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	opts->out = (unsigned char *)ft_memalloc(((r / 3) + 1) * 4 + 1 +
		(((r / 3) + 1) * 4 + 1) / 64 + 1);
	while (i < r)
	{
		b54_encryption(opts, &i, &j, r);
		if (j && ((j + 1) % 65 == 0) && opts->entered_key && (i != r - 1))
			opts->out[j++] = '\n';
		i++;
	}
	opts->out[j] = '\n';
	opts->out[j + 1] = '\0';
	write(opts->fd, opts->out, j + 1);
	free(opts->out);
}

void			b64(t_opt *opts)
{
	ssize_t			r;

	opts->fd = !opts->input_file ? 0 : open(opts->input_file, O_RDONLY);
	if (opts->fd == -1)
		return (put_open_err(opts->input_file));
	opts->in = (unsigned char *)get_from_fd(opts->fd, &r);
	close(opts->fd);
	if (!opts->output_file)
		opts->fd = 1;
	else if ((opts->fd = open(opts->output_file,
			O_CREAT | O_WRONLY | O_TRUNC, 0644)) == -1)
		return (put_open_err(opts->output_file));
	if (opts->d)
	{
		opts->out = b64_decode(opts->in, &r);
		write(opts->fd, opts->out, r);
		free(opts->out);
	}
	else
		b64_encode(opts, r);
	close(opts->fd);
	free(opts->in);
}
