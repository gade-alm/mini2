/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gade-alm <gade-alm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 15:39:01 by gade-alm          #+#    #+#             */
/*   Updated: 2023/05/10 13:12:39 by gade-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*ft_word(const char *s, char *word, int len)
{
	int		i;
	int		j;

	i = 0;
	j = -1;
	while (s[++j] == ' ' || s[j] == '\t')
		;
	while (s[j] && j < len)
		word[i++] = s[j++];
	word[i] = '\0';
	return (word);
}

int	count_args(char *str)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i])
	{
		i = is_space(str, i);
		if (str[i] == '<' || str[i] == '<' || str[i] == '|')
			i = char_delim(str, i, "<>|");
		else if (str[i])
			i = char_delim(str, i, " \t<>|");
		else
			break ;
		count++;
	}
	return (count);
}

char	**ft_split(char *str)
{
	int		i;
	char	**split;
	int		num_args;
	int		word_size;

	if (!str || !str[0])
		return (NULL);
	num_args = count_args(str);
	split = malloc(sizeof(char *) * (num_args + 1));
	if (!split)
		printerror("malloc error", 2);
	i = -1;
	while (++i < num_args)
	{
		word_size = token_len(str);
		split[i] = alloc_string(str);
		split[i] = ft_word(str, split[i], word_size);
		str += word_size;
	}
	split[i] = NULL;
	return (split);
}
