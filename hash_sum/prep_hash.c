/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_hash.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ulliwy <Ulliwy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 14:34:02 by iprokofy          #+#    #+#             */
/*   Updated: 2018/07/11 16:24:57 by Ulliwy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_hash.h"
#include "libft.h"
#include "ft_err.h"
#include "ft_ssl.h"
#include <fcntl.h> // for open
#include <errno.h>
#include <unistd.h>
#include <stdio.h>

void (*hash_func[2])(unsigned char *msg, ssize_t size, t_hash *opts) =
{
	&md5,
	&sha256
};

void		parse_opts(int argc, char **argv, t_hash *opts, int *err)
{
	int opt;

	while ((opt = getopt(argc, argv, "qrps:")) != -1)
	{
		if (opt == 'q')
		{
			opts->q = 1;
	 		opts->r = 0;
		}
		else if (opt == 'r')
			opts->r = 1;
		else if (opt == 's')
		{
			opts->s = 1;
			opts->str = (unsigned char *)optarg;
			opts->str_len = (ssize_t)ft_strlen(optarg);
			(hash_func[opts->id])(opts->str, opts->str_len, opts);
			opts->str = NULL;

		}
		else if (opt == 'p')
		{
			opts->p = 1;
			opts->pp = 1;
			opts->input = (unsigned char *)get_from_fd(0, &(opts->input_size));
			(hash_func[opts->id])(opts->input, opts->input_size, opts);
			free(opts->input);
		}
		else
		{
			*err = 1;
			md5_err_usage(argv[1]);
		}
	}
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

void	hash_file(char *file_name, t_hash *opts, char *exec)
{
	int fd;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		return (hash_open_err(file_name, exec, ft_strlen(exec)));
	opts->from_file = (unsigned char *)get_from_fd(fd, &(opts->file_size));
	if (errno)
	{
		hash_open_err(file_name, exec, ft_strlen(exec));
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
	int err;

	err = 0;
	hash_opts_init(&opts, func_id);
	i = 2;
	optind = 2;
	parse_opts(argc, argv, &opts, &err);
	if (optind < argc)
		while (optind < argc)
		{
			opts.filename = argv[optind];
			hash_file(argv[optind], &opts, argv[0]);
			optind++;
		}
	else if (!opts.p && !opts.s && !err)
	{
		opts.input = (unsigned char *)get_from_fd(0, &(opts.input_size));
		(hash_func[opts.id])(opts.input, opts.input_size, &opts);
		free(opts.input);
	}
	return (err);
	// return 1 in case of error
}
