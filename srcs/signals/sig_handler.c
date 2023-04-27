/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebin <grebin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 19:14:38 by gabriel           #+#    #+#             */
/*   Updated: 2023/04/27 17:31:05 by grebin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/* The value of the exit is 128 + the signal value, SIGINT
(ctrl+c) = 2 and SIGTSTOP (ctrl + \) = 3*/
void	sig_handler(int signal)
{
	if (signal == SIGQUIT)
	{
		this()->status = 131;
		return ;
	}
	if (signal == SIGINT)
	{
		this()->status = 130;
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	return ;
}
