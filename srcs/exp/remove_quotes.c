/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gade-alm <gade-alm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 16:50:22 by gade-alm          #+#    #+#             */
/*   Updated: 2023/04/13 12:46:16 by gade-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*remove_quotes(char *str, int i, int j)
{
	str = remove_single_quotes(str, i, j);
	str = remove_double_quotes(str, i, j);
	return (str);
}

char	*remove_double_quotes(char *str, int i, int j)
{
	char	*temp;
	int		ck_double;

	ck_double = 0;
	temp = alloc_string(str);
	while (str[++i])
	{
		if (str[i] != '"')
			temp[j] = str[i];
		if (str[i] == '"' && ck_double == 0)
		{
			temp[j] = str[i + 1];
			ck_double = 1;
			while (str[++i] != '"')
				temp[j++] = str[i];
			if (str[i] == '"')
				ck_double = 0;
		}
		else
			temp[j++] = str[i];
	}
	temp[j] = 0;
	free (str);
	return (temp);
}

char	*remove_single_quotes(char *str, int i, int j)
{
	char	*temp;
	int		ck_single;

	ck_single = 0;
	temp = alloc_string(str);
	while (str[++i])
	{
		if (str[i] != '\'')
			temp[j] = str[i];
		if (str[i] == '\'' && ck_single == 0)
		{
			temp[j] = str[i + 1];
			ck_single = 1;
			while (str[++i] != '\'')
				temp[j++] = str[i];
			if (str[i] == '\'')
				ck_single = 0;
		}
		else
			temp[j++] = str[i];
	}
	temp[j] = 0;
	free (str);
	return (temp);
}
