/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listutils_01.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebin <grebin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 13:44:02 by hcoutinh          #+#    #+#             */
/*   Updated: 2023/03/23 10:54:50 by grebin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/lists.h"

// Create a new node and return pointer to new obj.
t_cmd	*createnode(char **cmd)
{
	t_cmd	*objs;

	objs = malloc(sizeof(t_cmd));
	if (!objs)
		return (NULL);
	objs->input = 0;
	objs->output = 1;
	objs->path = NULL;
	objs->cmd = cmd;
	objs->next = NULL;
	return (objs);
}

// Add a node to the start and return first obj.
t_cmd	*addtostart(t_cmd **list, t_cmd *new)
{
	if (!new)
		return (NULL);
	if (!list)
		*list = new;
	else
	{
		new->next = *list;
		*list = new;
	}
	return (new);
}

// Add a node to the end and return last obj.
t_cmd	*addtolast(t_cmd **list, t_cmd *new)
{
	t_cmd	*temp;

	if (*list)
	{
		temp = *list;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
		temp = temp->next;
	}
	else
		*list = new;
	return (new);
}

// Remove a node on a specific position.
void	rmnode(t_cmd **list)
{
	t_cmd	*temp;
	int		i;

	temp = selectnode(*list, 0);
	if (!temp)
		return ;
	(*list) = (*list)->next;
	i = -1;
	if (temp->cmd)
	{
		while (temp->cmd[++i])
			free(temp->cmd[i]);
		free(temp->cmd);
	}
	if (temp->path)
		free(temp->path);
	if (temp)
		free(temp);
}

// Remove list.
void	rmlist(t_cmd **list)
{
	while (*list)
		rmnode(list);
}
