/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 08:52:38 by grebin            #+#    #+#             */
/*   Updated: 2023/05/08 15:47:42 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/executor.h"

t_sig	*sigcall(void)
{
	static t_sig	sig;

	return (&sig);
}

char	*expand_var_loop(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'')
			while (str[i] && str[i] != '\'')
				i++;
		if (str[i] == '$' && str[i + 1])
		{
			str = expand_var(str, this()->env, i);
			i = -1;
		}
	}
	return (str);
}

static void	heredocs_sig_handler(int signal)
{
	if (signal == SIGQUIT)
		printf("\b\b  \b\b");
	if (signal == SIGINT)
	{
		if (sigcall()->value[1] != -1)
		{
			close(sigcall()->value[1]);
			this()->status = 130;
			rl_clear_history();
			write (1, "\n", 1);
			exit(this()->status);
		}
	}
	return ;
}

void	forks_heredocs(char *temp, char *delim)
{
	signal(SIGQUIT, heredocs_sig_handler);
	signal(SIGINT, heredocs_sig_handler);
	close (sigcall()->value[0]);
	while (1)
	{
		if (temp)
		{
			temp = expand_var_loop(temp);
			prints(temp, sigcall()->value[1], NULL);
			free(temp);
		}
		temp = readline("<<: ");
		if (!temp)
			heredocs_ctrl_d(temp, delim);
		if (here_comp(temp, delim) == 1)
			break ;
	}
	if (temp)
		free(temp);
	exit(this()->status);
}

int	heredocs(char *delim)
{
	int	pid_heredocs;

	if (pipe(sigcall()->value) == -1)
		return (-1);
	pid_heredocs = fork();
	if (pid_heredocs == -1)
	{
		printf("ERRO NO HEREDOCS RESOLVE AI HENRIQUE\n");
		return (-1);
	}
	else if (pid_heredocs == 0)
		forks_heredocs(NULL, delim);
	wait(&this()->status);
	update_status(this());
	close(sigcall()->value[1]);
	return (sigcall()->value[0]);
}
