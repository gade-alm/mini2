/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listsred.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gade-alm <gade-alm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 08:28:28 by grebin            #+#    #+#             */
/*   Updated: 2023/04/17 12:56:06 by gade-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/lists.h"

t_red	*createred(int in, int out, int fd, char *delim)
{
	t_red	*red;

	red = malloc(sizeof(t_red));
	if (!red)
		return (NULL);
	red->delim = delim;
	red->in = in;
	red->out = out;
	red->fd = fd;
	red->next = NULL;
	return (red);
}

t_red	*addred(t_red **list, t_red *new)
{
	t_red	*temp;

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

void	rmred(t_red **red, int list)
{
	int		i;
	t_red	*temp;

	i = 0;
	while (*red && i == 0)
	{
		temp = *red;
		(*red) = (*red)->next;
		if (temp->delim)
			free(temp->delim);
		free(temp);
		if (list == 0)
			i++;
	}
}