/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ulliwy <Ulliwy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 15:33:44 by iprokofy          #+#    #+#             */
/*   Updated: 2018/07/05 14:26:35 by Ulliwy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ssl.h"

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

void	opts_init(t_opt *opts, t_cmd *cmd)
{
	opts->d = 0;
	opts->a = 0;
	opts->iv = 0;
	opts->v = 0;
	opts->prev = 0;
	opts->entered_key = NULL;
	opts->entered_iv = NULL;
	opts->input_file = NULL;
	opts->output_file = NULL;
	opts->in = NULL;
	opts->out = NULL;
	opts->cmd = cmd;
	opts->keys[0] = 0;
	opts->keys[1] = 0;
	opts->keys[2] = 0;
}

void	cmd_init(t_cmd *cmd)
{
	cmd->b64 = 0;
	cmd->ecb = 0;
	cmd->cbc = 0;
	cmd->ecb3 = 0;
	cmd->cbc3 = 0;
	cmd->md5 = 0;
}
