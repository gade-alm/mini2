/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gade-alm <gade-alm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 15:38:11 by grebin            #+#    #+#             */
/*   Updated: 2023/04/13 12:31:15 by gade-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	pipe_handler(t_cmd *first, t_cmd *second)
{
	int fd[2];

	if (pipe(fd) == -1)
		return (prints("pipe error", 2));
	if (first->input == 0)
		first->input = fd[1];
	else
		close(fd[1]);
	if (second->output == 1)
		second->input = fd[0];
	else
		close(fd[0]);
	return (0);
}

void	red_handler(int i, char *file, int ncmd)
{
	if (i == 1)
	{
		if (selectnode(this()->cmds, ncmd)->input != 0)
			close(selectnode(this()->cmds, ncmd)->input);
		selectnode(this()->cmds, ncmd)->input = open(file, O_RDONLY);
	}
	if (i == 2)
	{	
		if (selectnode(this()->cmds, ncmd)->input != 0)
			close(selectnode(this()->cmds, ncmd)->input);
		selectnode(this()->cmds, ncmd)->input = heredocs(file);
	}
	if (i == 3)
	{
		if (selectnode(this()->cmds, ncmd)->output != 1)
			close(selectnode(this()->cmds, ncmd)->output);
		selectnode(this()->cmds, ncmd)->output = open(file, O_CREAT, O_TRUNC, 0644);
	}
	if (i == 4)
	{
		if (selectnode(this()->cmds, ncmd)->output != 1)
			close(selectnode(this()->cmds, ncmd)->output);
		selectnode(this()->cmds, ncmd)->output = open(file, O_CREAT, O_APPEND, 0644);
	}
}

char **fill_cmd(char *next, int ncmd)
{
	char **temp;
	char **cmd;
	int	i;

	i = 0;
	cmd = selectnode(this()->cmds, ncmd)->cmd;
	temp = ft_realloc(cmd, 1);
	while (cmd && cmd[i])
	{
		temp[i] = ft_strdup(cmd[i]);
		if (!temp[i++])
		{
			free_matrix(temp);
			printerror("malloc error", 2);
		}
	}
	temp[i] = ft_strdup(next);
	if (!temp[i])
		printerror("malloc error", 2);
	temp[++i] = NULL;
	free_matrix(cmd);
	selectnode(this()->cmds, ncmd)->cmd = temp;
	return (temp);
}

int	set_cmd(char **arg, int i, int ncmd)
{
	while (arg && arg[i] && arg[i][0] != '|')
	{
		if((arg[i][0] == '<' || arg[i][0] == '>'))
			red_handler((arg[i][0] == '<') + (3 * (arg[i][0] == '>')) + (ft_strlen(arg[i]) == 2), arg[i + 1], ncmd);
		else
			fill_cmd(arg[i], ncmd);
		i += (arg[i][0] == '<' || arg[i][0] == '>') + 1;
	}
	return (i + (arg[i] && arg[i][0] == '|'));
}

char	**check_path(char **str, int i, int ncmd)
{
	char *temp;
	char *temp2;

	temp = ft_strrchr(str[i], '/');
	if (!temp)
		return (str);
	selectnode(this()->cmds, ncmd)->path = ft_strdup(str[i]);
	temp2 = str[i];
	str[i] = ft_strdup(temp + 1);
	free(temp2);
	return (str);
}

void cmds_split(char **arg)
{
	int	i;
	int	ncmd;

	ncmd = 0;
	i = 0;
	while (arg && arg[i])
	{
		addtolast(&this()->cmds, createnode(NULL));
		arg = check_path(arg, i, ncmd);
		i = set_cmd(arg, i, ncmd);
		ncmd++;
	}
	while (--ncmd > 0)
		pipe_handler(selectnode(this()->cmds, ncmd - 1), selectnode(this()->cmds, ncmd));
	// printlist(this()->cmds);
	if (arg)
		free_matrix(arg);
}
