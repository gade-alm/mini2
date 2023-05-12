/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gade-alm <gade-alm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 15:44:42 by grebin            #+#    #+#             */
/*   Updated: 2023/05/12 12:53:31 by gade-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_path(t_cmd *cmd)
{
	char	*temp;
	char	*temp2;

	if (!cmd->cmd || !*cmd->cmd)
		return (0);
	temp = ft_strrchr(cmd->cmd[0], '/');
	if (!temp)
		return (1);
	cmd->path = ft_strdup(cmd->cmd[0]);
	temp2 = cmd->cmd[0];
	cmd->cmd[0] = ft_strdup(temp + 1);
	free(temp2);
	return (1);
}

void	path_temp(void)
{
	t_cmd	*temp;

	temp = this()->cmds;
	while (temp)
	{
		check_path(temp);
		temp = temp->next;
	}
}

void	red_handler2(int i, char *file, int ncmd)
{
	if (i == 3)
	{
		if (selectnode(this()->cmds, ncmd)->output != 1)
			close(selectnode(this()->cmds, ncmd)->output);
		(selectnode)(this()->cmds, ncmd)->output = \
		open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	}
	if (i == 4)
	{
		if (selectnode(this()->cmds, ncmd)->output != 1)
			close(selectnode(this()->cmds, ncmd)->output);
		(selectnode)(this()->cmds, ncmd)->output = \
		open(file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	}
}

void	red_handler(int i, char *file, int ncmd)
{
	if (i == 1)
	{
		if (selectnode(this()->cmds, ncmd)->input == -1)
			return ;
		if (selectnode(this()->cmds, ncmd)->input != 0)
			close(selectnode(this()->cmds, ncmd)->input);
		(selectnode)((this())->cmds, ncmd)->input = open(file, O_RDONLY);
		if ((selectnode)((this())->cmds, ncmd)->input == -1)
		{
			(selectnode)((this())->cmds, ncmd)->error = 1;
			(selectnode)((this())->cmds, ncmd)->errormsg = ft_strdup(file);
		}
	}
	if (i == 2)
	{
		if (selectnode(this()->cmds, ncmd)->input != 0)
			close(selectnode(this()->cmds, ncmd)->input);
		(selectnode)(this()->cmds, ncmd)->input = heredocs(file);
	}
	red_handler2(i, file, ncmd);
}
