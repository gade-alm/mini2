/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gade-alm <gade-alm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 08:52:38 by grebin            #+#    #+#             */
/*   Updated: 2023/05/03 12:23:00 by gade-alm         ###   ########.fr       */
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

void	heredocs_ctrl_d(char *temp, char *delim)
{
	(void)delim;
	if (temp)
		return ;
	if (sigcall()->value[1] != -1)
		close (sigcall()->value[1]);
	printf("bash: warning(wanted %s)\n", delim);
	rl_clear_history();
	free (temp);
	exit(this()->status);
}

void	heredocs_sig_handler(int signal)
{
	if (signal == SIGQUIT)
		return ;
	if (signal == SIGINT)
	{
		if (sigcall()->value[1] != -1)
		{
			close(sigcall()->value[1]);
			this()->status = 130;
			write (1, "\n", 1);
			sigcall()->check = 1;
			exit(this()->status);
		}
	}
	return ;
}

void	forks_heredocs(char *temp, char *delim)
{
	signal(SIGINT, heredocs_sig_handler);
	signal(SIGQUIT, heredocs_sig_handler);
	close (sigcall()->value[0]);
	while (ft_strncmp(temp, delim, ft_strlen(temp)) != 0)
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
	wait(NULL);
	close(sigcall()->value[1]);
	return (sigcall()->value[0]);
}
