/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gade-alm <gade-alm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 19:13:38 by gabriel           #+#    #+#             */
/*   Updated: 2023/05/15 10:32:43 by gade-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	a;

	a = 0;
	if (n == 0)
		return (-1);
	if (!s1 || !s2)
		return (-1);
	while ((s1[a] != 0) && (s2 != 0) && (s1[a] == s2[a]) && (a < n - 1))
		a++;
	return ((unsigned char)s1[a] - (unsigned char)s2[a]);
}

int	verify_var(char *str, char *env)
{
	int	i;

	i = -1;
	while (str[++i] && env[i] != '=' && str[i] == env[i])
		;
	return (!str[i] && env[i] == '=');
}

int	env_char(char c)
{
	if ((c >= '0' && c <= '9' ) || (c >= 'A' && c <= 'Z') || \
	(c >= 'a' && c <= 'z') || c == '_' || c == '?')
		return (1);
	return (0);
}
