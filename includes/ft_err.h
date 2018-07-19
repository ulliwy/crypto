/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_err.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iprokofy <iprokofy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 14:49:35 by iprokofy          #+#    #+#             */
/*   Updated: 2018/07/19 10:42:17 by iprokofy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ERR_H
# define FT_ERR_H

void	put_open_err(char *name);
int		err_usage(int type);
int		err_options(char cmd);
int		err_usage_commands(char *cmd);
int		put_iv_err(int type);
void	*put_stream_err(void);
int		put_key_err(void);
int		md5_err_usage(char *command);
int		md5_err_options(char opt, char *command);

#endif
