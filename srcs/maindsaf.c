/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gade-alm <gade-alm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 11:13:25 by gabriel           #+#    #+#             */
/*   Updated: 2023/04/11 12:00:10 by gade-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	main(int ac, char **av, char **envp)
{
	char			*str;
	static t_args	args;

	(void)ac;
	(void)av;
	(void)args;
	signal(SIGINT, sig_handler);
	envs()->env = create_env(envp);
	while (1)
	{
		str = readline("$>>:");
		if (str && *str)
		{
			add_history(str);
			if (check_string(str))
			{
				if (strcmp("exit", str) == 0)
					return (0);
				args.cmd = handle_commands(str, envp);
				for (int i = 0; i < count_args(str); i++)
					printf("%s\n", args.cmd[i]);
				free (str);
			}
		}
		if (!str)
		{
			write (1, "exit\n", 5);
			exit(this()->status);
		}
	}
	return (0);
}
