/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebin <grebin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 15:21:40 by grebin            #+#    #+#             */
/*   Updated: 2023/04/27 16:07:00 by grebin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/builtins.h"

char	*get_home(char **env)
{
	char	*home;
	char	*temp;

	home = NULL;
	temp = check_var("HOME=", env, 4);
	if (temp)
		home = ft_strdup(temp + 5);
	return (home);
}

int	cd_home(char **env, t_cmd *node)
{
	char	**tmp;	
	char	*home;

	home = get_home(env);
	if (!home)
		return (prints("HOME not set", 2, NULL));
	tmp = node->cmd;
	node->cmd = malloc(sizeof(char *) * (3));
	if (!node->cmd)
		return (2);
	node->cmd[0] = tmp[0];
	node->cmd[1] = home;
	node->cmd[2] = NULL;
	free(tmp);
	return (0);
}