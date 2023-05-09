/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 16:50:22 by gade-alm          #+#    #+#             */
/*   Updated: 2023/05/09 22:16:47 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*remove_char(char *str, char c, int *i)
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
			str[++k] = str[j];
	}
	str[++k] = 0;
	return (str);
}

char	*remove_quotes(char *str)
{
	int		i;
	char	*temp;

	i = 0;
	temp = ft_strdup(str);
	if (!temp)
		printerror("malloc error", 2);
	while (temp[i])
	{
		if (temp[i] && temp[i] == '\'')
			remove_char(temp, '\'', &i);
		else if (temp[i] && temp[i] == '"')
			temp = remove_char(temp, '"', &i);
		else
			i++;
		if (!temp[i])
			break ;
	}
	free (str);
	return (temp);
}

// char	*remove_double_quotes(char *str, int i, int j)
// {
// 	char	*temp;
// 	int		ck_double;

// 	ck_double = 0;
// 	temp = alloc_string(str);
// 	while (str[++i])
// 	{
// 		if (str[i] != '"')
// 			temp[j] = str[i];
// 		if (str[i] == '"' && ck_double == 0)
// 		{
// 			temp[j] = str[i + 1];
// 			ck_double = 1;
// 			while (str[++i] != '"')
// 				temp[j++] = str[i];
// 			if (str[i] == '"')
// 				ck_double = 0;
// 		}
// 		else
// 			temp[j++] = str[i];
// 	}
// 	temp[j] = 0;
// 	free (str);
// 	return (temp);
// }

// char	*remove_single_quotes(char *str, int i, int j)
// {
// 	char	*temp;
// 	int		ck_single;

// 	ck_single = 0;
// 	temp = alloc_string(str);
// 	while (str[++i])
// 	{
// 		if (str[i] != '\'')
// 			temp[j] = str[i];
// 		if (str[i] == '\'' && ck_single == 0)
// 		{
// 			temp[j] = str[i + 1];
// 			ck_single = 1;
// 			while (str[++i] != '\'')
// 				temp[j++] = str[i];
// 			if (str[i] == '\'')
// 				ck_single = 0;
// 		}
// 		else
// 			temp[j++] = str[i];
// 	}
// 	temp[j] = 0;
// 	free (str);
// 	return (temp);
// }
