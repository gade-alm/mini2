/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gade-alm <gade-alm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 08:52:38 by grebin            #+#    #+#             */
/*   Updated: 2023/04/28 11:57:29 by gade-alm         ###   ########.fr       */
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

void	heredocs_sig_handler(int signal)
{
	if (signal == SIGINT)
	{
		if (sigcall()->value[1] != -1)
		{
			close(sigcall()->value[1]);
			this()->status = 130;
			write (1, "\n", 1);
			exit(this()->status);
		}
	}
	return ;
}

void	forks_heredocs(char *temp, char *delim)
{
	int	pid;

	signal(SIGINT, heredocs_sig_handler);
	signal(SIGQUIT, heredocs_sig_handler);
	pid = fork();
	if (pid == -1)
	{
		printf("error on heredoc forks");
		return ;
	}
	else if (pid == 0)
	{
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
		}
		if (temp)
			free(temp);
	}
	return ;
}

int	heredocs(char *delim)
{
	if (pipe(sigcall()->value) == -1)
		return (-1);
	forks_heredocs(NULL, delim);
	close(sigcall()->value[1]);
	return (sigcall()->value[0]);
}
