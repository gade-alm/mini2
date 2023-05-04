/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 15:44:42 by grebin            #+#    #+#             */
/*   Updated: 2023/05/04 16:01:50 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	red_handler2(int i, char *file, int ncmd)
{
	if (i == 3)
	{
		if (selectnode(this()->cmds, ncmd)->output != 1)
			close(selectnode(this()->cmds, ncmd)->output);
		(selectnode)(this()->cmds, ncmd)->output = \
		open(file, O_CREAT | O_TRUNC, 0644);
	}
	if (i == 4)
	{
		if (selectnode(this()->cmds, ncmd)->output != 1)
			close(selectnode(this()->cmds, ncmd)->output);
		(selectnode)(this()->cmds, ncmd)->output = \
		open(file, O_CREAT | O_APPEND, 0644);
	}
}

void	red_handler(int i, char *file, int ncmd)
{
	if (i == 1)
	{
		if (selectnode(this()->cmds, ncmd)->input != 0)
			close(selectnode(this()->cmds, ncmd)->input);
		(selectnode)((this())->cmds, ncmd)->input = open(file, O_RDONLY);
	}
	if (i == 2)
	{
		if (selectnode(this()->cmds, ncmd)->input != 0)
			close(selectnode(this()->cmds, ncmd)->input);
		(selectnode)(this()->cmds, ncmd)->input = heredocs(file);
	}
	red_handler2(i, file, ncmd);
}
