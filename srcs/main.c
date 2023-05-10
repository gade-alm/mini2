/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gade-alm <gade-alm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 11:13:25 by gabriel           #+#    #+#             */
/*   Updated: 2023/05/10 11:01:59 by gade-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

void	history_parse(char *str)
{
	signal(SIGINT, sig_test);
	add_history(str);
	if (check_string(str))
	{
		cmds_split(handle_commands(str, this()->env, -1));
		executor(this()->cmds);
	}
	return ;
}

int	main(int ac, char **av, char **envp)
{
	char	*str;

	(void)ac;
	(void)av;
	this()->env = create_env(envp);
	while (1)
	{
		signal(SIGINT, sig_handler);
		signal(SIGQUIT, SIG_IGN);
		str = readline("$minishell:");
		if (str && *str)
			history_parse(str);
		else if (!str)
		{
			rl_clear_history();
			printerror("exit", 1);
		}
		free (str);
	}
}
