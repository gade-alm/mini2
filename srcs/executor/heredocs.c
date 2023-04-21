/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gade-alm <gade-alm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 08:52:38 by grebin            #+#    #+#             */
/*   Updated: 2023/04/21 12:11:58 by gade-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/executor.h"

int	*check_fd(int *fd)
{
	static int	*ret;

	if (fd)
		ret = fd;
	return (ret);
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
	int	fd;

	fd = *check_fd(NULL);
	if (signal == SIGQUIT)
		return ;
	if (signal == SIGINT)
	{
		fd = *check_fd(NULL);
		printf("%i\n", fd);
		if (fd != -1)
			close(fd);
		this()->status = 130;
	}
	return ;
}

int	heredocs(char *delim)
{
	char		*temp;
	int			fd[2];

	signal(SIGINT, heredocs_sig_handler);
	signal(SIGKILL, heredocs_sig_handler);
	temp = NULL;
	if (pipe(fd) == -1)
		return (-1);
	check_fd(fd);
	printf("%i\n", fd[0]);
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
