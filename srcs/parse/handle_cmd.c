/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gade-alm <gade-alm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 10:44:03 by gade-alm          #+#    #+#             */
/*   Updated: 2023/04/13 12:52:36 by gade-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	**handle_commands(char *str, char **env)
{
	char	**split;
	int		i;
	int		j;

	i = -1;
	split = ft_split(str);
	if (!split)
		return (0);
	while (split[++i])
	{
		j = -1;
		while (split[i][++j])
		{
			if (split[i][j] == '\'')
				while (split[i][++j] && split[i][j] != '\'')
					;
			if (split[i][j] == '$' && split[i][j + 1])
			{
				split[i] = expand_var(split[i], env, j);
				j = -1;
			}
		}
		split[i] = remove_quotes(split[i], -1, 0);
	}
	return (split);
}
