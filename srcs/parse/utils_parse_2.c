/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parse_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gade-alm <gade-alm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 17:03:51 by gade-alm          #+#    #+#             */
/*   Updated: 2023/03/29 15:52:59 by gade-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	check_single_quote(char *str, int i)
{
	if (!str[i + 1])
	{
		printf("Check Quotes\n");
		return (0);
	}
	while (str[i++])
	{
		if (str[i] == '\'')
			return (i);
	}
	printf("Check Quotes\n");
	return (0);
}

int	check_double_quote(char *str, int i)
{
	if (!str[i + 1])
	{
		printf("Check Quotes\n");
		return (0);
	}
	while (str[++i])
	{
		if (str[i] == '\"')
			return (i);
	}
	printf("Check Quotes\n");
	return (0);
}

int	check_pipe(char *str, int i)
{
	i++;
	if (str[i] == '|')
	{
		i++;
		if (str[i] == '|')
		{
			printf("Check Pipes\n");
			return (0);
		}
	}
	return (i);
}

int	check_string(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'')
		{
		i = check_single_quote(str, i);
			if (!i)
				return (0);
		}
		if (str[i] == '\"')
		{
		i = check_double_quote(str, i);
			if (!i)
				return (0);
		}
		if (str[i] == '|')
		{
			i = check_pipe(str, i);
			if (!i)
				return (0);
		}
		if (str[i] == '>')
		{
			while (str[i++] == ' ' || str[i] == '\t')
				;
			if (!str[i])
			{
				printf("Error on Redir\n");
				return (0);
			}
		}
	}
	return (i);
}
