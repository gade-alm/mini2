/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gade-alm <gade-alm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 12:01:47 by gade-alm          #+#    #+#             */
/*   Updated: 2023/03/30 16:43:41 by gade-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/strings.h"

int	ft_strlen(const char *str)
{
	int	i;

	i = -1;
	if (!str)
		return 0;
	while (str[++i])
		;
	return (i);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = -1;
	if (!s1 )
		return (0);
	while ((s1[++i] && s2[i]) && (s1[i] == s2[i]))
		;
	if (i == ft_strlen(s1))
		return (1);
	return (0);
}

char	*ft_strrchr(const char *s, int c)
{
	char	*str;
	int		len;

	if (!s)
		return (NULL);
	len = -1;
	str = (char *)s;
	while (str[++len])
		;
	while (len >= 0)
	{
		if (str[len] == (char) c)
			return ((char *)&str[len]);
		len--;
	}
	return (NULL);
}

char	*ft_strchr(const char *s, int c)
{
	char	*str;
	int		a;

	if (!s)
		return (NULL);
	a = -1;
	str = (char *) s;
	while (str[++a] && str[a] != (char)c)
		if (str[a] == '\0')
			return (NULL);
	return (&str[a]);
}
