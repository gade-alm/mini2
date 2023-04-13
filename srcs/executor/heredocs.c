/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcoutinh <hcoutinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 08:52:38 by grebin            #+#    #+#             */
/*   Updated: 2023/03/28 14:43:34 by hcoutinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/executor.h"


int heredocs(char *delim)
{
	char	*temp;
	int 	fd[2];

	temp = NULL;
	if (pipe(fd) == -1)
		return (-1);
	while (ft_strncmp(temp, delim, ft_strlen(temp)) != 0)
	{
		if (temp)
		{
			// meter o expand
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
