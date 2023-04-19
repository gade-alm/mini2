/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parse_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gade-alm <gade-alm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 17:03:51 by gade-alm          #+#    #+#             */
/*   Updated: 2023/04/19 10:50:33 by gade-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	check_single_quote(char *str, int i, char quote)
{
	if (!str[i + 1])
	{
		printf("Check Quotes\n");
		return (0);
	}
	while (str[i++])
	{
		if (str[i] == quote)
			return (i);
	}
	printf("Check Quotes\n");
	return (0);
}

int	check_pipe(char *str, int i)
{
	if (str[i] && str[i + 1] == '|')
	{
		printf("Check Pipes\n");
		return (0);
	}
	return (i);
}

int	check_string(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			i = check_single_quote(str, i, str[i]);
			if (!i)
				return (0);
		}
		if (str[i] == '|')
		{
			i = check_pipe(str, i);
			if (!i)
				return (0);
		}
	}
	if (check_strings_2(str) == 1)
		return (1);
	return (0);
}

int	check_redir(char *str, int i)
{
	i++;
	while (str[i] != '|' && (str[i] == ' ' || str[i] == '\t'))
		i++;
	if (str[i] == '|' || !str[i])
		return (0);
	return (i);
}

int	check_heredocs(char *str, int i)
{
	i += 2;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (!str[i])
		return (0);
	return (1);
}

int	check_strings_2(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '>')
		{
			i = check_redir(str, i);
			if (!i)
			{
				printf("Error on >\n");
				return (0);
			}
		}
		if (str[i] == '<' && str[i + 1] == '<')
		{
			i = check_heredocs(str, i);
			if (!i)
			{
				printf("zsh: parse error near '\\n'\n");
				return (0);
			}
		}
	}
	return (1);
}
