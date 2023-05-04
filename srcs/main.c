/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 11:13:25 by gabriel           #+#    #+#             */
/*   Updated: 2023/05/04 16:38:21 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

static void	sig_handler(int signal)
{
	if (signal == SIGQUIT)
		return ;
	if (signal == SIGINT && !this()->cmds)
	{
		this()->status = 130;
		write (1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	return ;
}

void	minishell(char *str)
{
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
	signal(SIGQUIT, sig_handler);
	signal(SIGINT, sig_handler);
	this()->env = create_env(envp);
	while (1)
	{
		str = readline("$minishell:");
		if (str && *str)
			minishell(str);
		else if (!str)
		{
			rl_clear_history();
			printerror("exit", 1);
		}
		free (str);
	}
}
