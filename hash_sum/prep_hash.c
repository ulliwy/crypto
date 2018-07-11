/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_hash.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ulliwy <Ulliwy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 14:34:02 by iprokofy          #+#    #+#             */
/*   Updated: 2018/07/10 16:53:21 by Ulliwy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_hash.h"
#include "libft.h"
#include "ft_err.h"
#include "ft_ssl.h"
#include <fcntl.h> // for open
#include <errno.h>

void (*hash_func[2])(unsigned char *msg, ssize_t size, t_hash *opts) =
{
	&md5,
	&sha256
};

static int		parse_opts(char **av, int i, t_hash *opts, int *parsed)
{
	if (av[i][0] == '-' && !av[i][2])
	{
		if (av[i][1] == 'q')
		{
			opts->q = 1;
			opts->r = 0;
		}
		else if (av[i][1] == 'r')
			opts->r = 1;
		else if (av[i][1] == 's' && av[i + 1])
		{
			opts->s = 1;
			opts->str = (unsigned char *)av[i + 1];
			opts->str_len = (ssize_t)ft_strlen(av[i + 1]);
			(hash_func[opts->id])(opts->str, opts->str_len, opts);
			opts->str = NULL;
			i++;
		}
		else if (av[i][1] == 'p')
		{
			opts->p = 1;
			opts->pp = 1;
			opts->input = (unsigned char *)get_from_fd(0, &(opts->input_size));
			(hash_func[opts->id])(opts->input, opts->input_size, opts);
			free(opts->input);
		}
		else
			return (md5_err_options(av[i][1]));
	}
	else
	{
		*parsed = i;
		return (1);
	}
	return (i + 1);
}

void	hash_opts_init(t_hash *opts, int func_id)
{
	opts->id = func_id;
	opts->q = 0;
	opts->r = 0;
	opts->s = 0;
	opts->p = 0;
	opts->pp = 0;
	opts->filename = NULL;

	opts->str = NULL;

	opts->input = NULL;
	opts->input_size = 0;

	opts->from_file = NULL;
	opts->file_size = 0;
}

void	hash_file(char *file_name, t_hash *opts)
{
	int fd;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		return (hash_open_err(file_name, "md5", 3));
	opts->from_file = (unsigned char *)get_from_fd(fd, &(opts->file_size));
	if (errno)
	{
		hash_open_err(file_name, "md5", 3);
		errno = 0;
	}
	else
	{
		(hash_func[opts->id])(opts->from_file, opts->file_size, opts);
		free(opts->from_file);
	}
	close(fd);
}

int			hash_prep(int argc, char **argv, int func_id)
{
	int 	i;
	t_hash	opts;
	int 	parsed;

	hash_opts_init(&opts, func_id);
	i = 2;
	parsed = 0;
	while (i < argc && !parsed)
	{
		i = parse_opts(argv, i, &opts, &parsed);
		if (i == 0)
			return (md5_err_usage());
	}
	while (parsed && parsed < argc)
	{
		opts.filename = argv[parsed];
		hash_file(argv[parsed], &opts);
		parsed++;
	}
	if (!opts.p && !opts.s && !parsed)
	{
		opts.input = (unsigned char *)get_from_fd(0, &(opts.input_size));
		(hash_func[opts.id])(opts.input, opts.input_size, &opts);
		free(opts.input);
	}
	return (0);
	// return 1 in case of error
}
