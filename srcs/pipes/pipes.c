/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebin <grebin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 11:49:43 by grebin            #+#    #+#             */
/*   Updated: 2023/02/15 11:56:34 by grebin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../pipes.h"

int	pipe_handler(t_cmd *first, t_cmd *second)
{
	int fd[2];

	if (pipe(fd) == -1)
		return (prints("pipe error", 2));
	if (first->input == 0)
		first->input = fd[0];
	else
		close(fd[0]);
	if (second->output == 1)
		first->input = fd[1];
	else
		close(fd[1]);
}

