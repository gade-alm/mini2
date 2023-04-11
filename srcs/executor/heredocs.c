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


int	prep_heredocs(char *arg)
{
	int fd[2];
	int n = 0;

	if (pipe(fd) == -1)
		return (-1);
	n = ft_strlen(arg);
	write(fd[1], arg, n);
	close(fd[1]);
	free(arg);
	return (fd[0]);
}

int heredocs(char *delim)
{
	char	*temp;
	char	*temp1;
	char	*temp2;
	char	*arg;

	temp = NULL;
	arg = NULL;
	while (ft_strncmp(temp, delim, ft_strlen(temp)) != 0)
	{
		if (temp)
			free(temp);
		temp = readline("<<: ");
		temp1 = ft_strjoin(temp, "\n");
		temp2 = arg;
		arg = ft_strjoin(arg, temp1);
		if (temp2)
			free(temp2);
		free(temp1);
	}
	if (temp)
		free(temp);
	return (prep_heredocs(arg));
}
