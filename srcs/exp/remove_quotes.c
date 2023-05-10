/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gade-alm <gade-alm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 16:50:22 by gade-alm          #+#    #+#             */
/*   Updated: 2023/05/10 12:27:19 by gade-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*remove_char(char *str, char c, int *i)
{
	char	*temp;
	int		check;
	int		j;
	int		k;

	check = 0;
	j = -1;
	k = -1;
	temp = malloc(sizeof(char) * (ft_strlen(str)) - 1);
	if (!temp)
		printerror("malloc error", 2);
	while (str[++j])
	{
		if (*i == j && check != 2)
			check++;
		else if (j > *i && str[j] == c && check != 2)
		{
			check++;
			*i = j - 1;
		}
		else
			temp[++k] = str[j];
	}
	temp[++k] = 0;
	free(str);
	return (temp);
}

char	*remove_quotes(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] && str[i] == '\'')
			str = remove_char(str, '\'', &i);
		else if (str[i] && str[i] == '"')
			str = remove_char(str, '"', &i);
		else
			i++;
		if (!str[i])
			break ;
	}
	return (str);
}
