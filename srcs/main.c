/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebin <grebin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 11:13:25 by gabriel           #+#    #+#             */
/*   Updated: 2023/04/12 22:44:31 by grebin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

int main(int ac, char **av, char **envp)
{
	char *str;

	(void)ac;
	(void)av;
	signal(SIGINT, sig_handler);
	signal(SIGKILL, sig_handler);
	this()->env = create_env(envp);
	while (1)
	{
		str = readline("$minishell:");
		if (str && *str)
		{
			add_history(str);
			cmds_split(handle_commands(str, this()->env));
			executor(this()->cmds);
		}
		if (!str)
		{
			rl_clear_history();
			printerror("exit", 1);
		}
	}
}
