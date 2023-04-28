/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gade-alm <gade-alm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 08:52:38 by grebin            #+#    #+#             */
/*   Updated: 2023/04/28 11:15:14 by gade-alm         ###   ########.fr       */
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
		printf("%i\n", sigcall()->value[1]);
		if (sigcall()->value[1] != -1)
		{
			close(sigcall()->value[1]);
			printf("TESTE\n");
			this()->status = 130;
		}
	}
	return ;
}

int	heredocs(char *delim)
{
	char		*temp;

	signal(SIGINT, heredocs_sig_handler);
	signal(SIGQUIT, heredocs_sig_handler);
	temp = NULL;
	if (pipe(sigcall()->value) == -1)
		return (-1);
	printf("%i\n", sigcall()->value[1]);
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
	close(sigcall()->value[1]);
	return (sigcall()->value[0]);
}
