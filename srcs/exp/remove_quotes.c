/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gade-alm <gade-alm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 16:50:22 by gade-alm          #+#    #+#             */
/*   Updated: 2023/05/12 13:04:10 by gade-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*copy_str(char *str, char *temp, int *i, char c)
{
	int		check;
	int		j;
	int		k;

	check = 0;
	j = -1;
	k = -1;
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
	return (temp);
}

char	*remove_char(char *str, char c, int *i)
{
	char	*temp;

	temp = malloc(sizeof(char) * (ft_strlen(str)) - 1);
	if (!temp)
		printerror("malloc error", 2);
	temp = copy_str(str, temp, i, c);
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
