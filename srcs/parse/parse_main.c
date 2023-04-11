/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebin <grebin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 15:38:11 by grebin            #+#    #+#             */
/*   Updated: 2023/04/04 18:22:59 by grebin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	red_handler(int i, char *file, int ncmd)
{
	//printf("%d\n", i);
	if (i == 1)
		selectnode(this()->cmds, ncmd)->input = open(file, O_RDONLY);
	if (i == 2)
		selectnode(this()->cmds, ncmd)->input = heredocs(file);
	if (i == 3)
		selectnode(this()->cmds, ncmd)->input = open(file, O_CREAT, O_TRUNC, 0644);
	if (i == 4)
		selectnode(this()->cmds, ncmd)->input = open(file, O_CREAT, O_APPEND, 0644);
}

char **fill_cmd(char *next, int ncmd)
{
	char **temp;
	char **cmd;
	int	i;

	i = 0;
	cmd = selectnode(this()->cmds, ncmd)->cmd;
	temp = alloc_matrix(cmd, 1);
	while (cmd && cmd[i])
	{
		temp[i] = ft_strdup(cmd[i]);
		if (!temp)
		{
			free_matrix(temp);
			return (NULL); // EXIT PROG
		}
		i++;
	}
	temp[i] = ft_strdup(next);
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
		{
			red_handler((arg[i][0] == '<') + (3 * (arg[i][0] == '>')) + (ft_strlen(arg[i]) == 2), arg[i + 1], ncmd);
		}
		else
			fill_cmd(arg[i], ncmd);
		i += (arg[i][0] == '<' || arg[i][0] == '>') + 1;
	}
	return (i + (arg[i] && arg[i][0] == '|'));
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
		i = set_cmd(arg, i, ncmd);
		//printf("%i\n", i);
		ncmd++;
	}
	free_matrix(arg);
}
