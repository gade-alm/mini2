/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gade-alm <gade-alm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 11:13:25 by gabriel           #+#    #+#             */
/*   Updated: 2023/05/03 10:59:54 by gade-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

int	main(int ac, char **av, char **envp)
{
	char	*str;

	(void)ac;
	(void)av;
	signal(SIGQUIT, sig_handler);
	signal(SIGINT, sig_handler);
	this()->env = create_env(envp);
	while (1)
	{
		str = readline("$minishell:");
		if (str && *str)
		{
			add_history(str);
			if (check_string(str))
			{
				cmds_split(handle_commands(str, this()->env, -1));
				executor(this()->cmds);
			}
		}
		else if (!str)
		{
			rl_clear_history();
			printerror("exit", 1);
		}
		free (str);
	}
}
