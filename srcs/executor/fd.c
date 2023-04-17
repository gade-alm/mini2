/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gade-alm <gade-alm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 08:52:38 by grebin            #+#    #+#             */
/*   Updated: 2023/04/17 11:22:11 by gade-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/executor.h"

int	prep_heredocs(char *arg)
{
	int	fd[2];
	int	n;

	n = 0;
	if (pipe(fd) == -1)
		return (-1);
	n = ft_strlen(arg);
	write(fd[1], arg, n);
	return (fd[0]);
}

int	heredocs(t_red *red)
{
	char	*temp;
	char	*temp1;
	char	*arg;

	temp = NULL;
	arg = NULL;
	while (ft_strncmp(temp, red->delim, ft_strlen(temp)) != 0)
	{
		free(temp);
		temp = readline("Minishell: ");
		temp1 = ft_strjoin(temp, "\n");
		arg = ft_strjoin(arg, temp1);
		free(temp1);
	}
	//printf("%s", arg);
	return (prep_heredocs(arg));
}

void	prep_fd(t_cmd *cmd)
{
	while (cmd->red)
	{
		if (cmd->red->in != 0 && cmd->input != 0)
			close (cmd->input);
		if (cmd->red->out != 1 && cmd->output != 1)
			close (cmd->output);
		if (cmd->red->in == 1)
			cmd->input = cmd->red->fd;
		if (cmd->red->in == 2)
		{
			if (cmd->lasthere != 0)
				close(cmd->lasthere);
			cmd->input = heredocs(cmd->red);
			cmd->lasthere = cmd->input;
		}
		if (cmd->red->out == 1)
			cmd->output = open(cmd->cmd[0], O_CREAT | O_TRUNC | O_WRONLY, 0644);
		if (cmd->red->out == 2)
			cmd->output = open(cmd->cmd[0], O_CREAT | \
			O_APPEND | O_WRONLY, 0644);
		cmd->red = cmd->red->next;
	}
}
