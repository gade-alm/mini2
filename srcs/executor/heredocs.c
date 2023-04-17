/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gade-alm <gade-alm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 08:52:38 by grebin            #+#    #+#             */
/*   Updated: 2023/04/17 11:44:52 by gade-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/executor.h"

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

int	heredocs(char *delim)
{
	char	*temp;
	int		fd[2];

	temp = NULL;
	if (pipe(fd) == -1)
		return (-1);
	while (ft_strncmp(temp, delim, ft_strlen(temp)) != 0)
	{
		if (temp)
		{
			temp = expand_var_loop(temp);
			prints(temp, fd[1], NULL);
			free(temp);
		}
		temp = readline("<<: ");
	}
	if (temp)
		free(temp);
	close(fd[1]);
	return (fd[0]);
}
