/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gade-alm <gade-alm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 19:14:38 by gabriel           #+#    #+#             */
/*   Updated: 2023/05/03 10:56:44 by gade-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/* The value of the exit is 128 + the signal value, SIGINT
(ctrl+c) = 2 and SIGTSTOP (ctrl + \) = 3*/
void	sig_handler(int signal)
{
	if (signal == SIGQUIT)
		return ;
	if (signal == SIGINT && sigcall()->check == 1)
	{
		this()->status = 130;
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	return ;
}
