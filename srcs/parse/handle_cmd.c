/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gade-alm <gade-alm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 10:44:03 by gade-alm          #+#    #+#             */
/*   Updated: 2023/05/09 12:18:35 by gade-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	check_double_redir(char **split, int i)
{
	if (split[i - 1][0] == '<' && split[i - 1][1] == '<')
		return (1);
	return (0);
}

int	not_expand(char *str, int i)
{
	while (str[++i] && str[i] != '\'')
		;
	return (i);
}

char	**handle_commands(char *str, char **env, int i)
{
	char		**split;
	int			j;
	static int	lower;

	split = ft_split(str);
	if (!split)
		return (0);
	while (split[++i])
	{
		j = -1;
		while (split[i][++j])
		{
			if (i > 0)
				lower = check_double_redir(split, i);
			if (split[i][j] == '\'')
				j = not_expand(split[i], j);
			if (split[i][j] == '$' && split[i][j + 1] && lower == 0)
			{
				split[i] = expand_var(split[i], env, j);
				j = -1;
			}
		}
		split[i] = remove_quotes(split[i]);
	}
	return (split);
}
