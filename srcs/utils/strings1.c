/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gade-alm <gade-alm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 13:39:06 by grebin            #+#    #+#             */
/*   Updated: 2023/05/05 09:52:55 by gade-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

long	ft_atoi(char *s)
{
	long	n;
	long	sig;

	n = 0;
	sig = 1;
	while (*s == 32 || (*s > 8 && *s < 14))
		s++;
	if (*s == '-' || *s == '+')
	{
		if (*s == '-')
			sig *= -1;
		s++;
	}
	while (*s >= '0' && *s <= '9')
	{
		n = n * 10 + sig * (*s - '0');
		s++;
	}

	return (n);
}

static int	ft_numdig(int n)
{
	if (n < 10 && n > -10)
		return (1);
	else
		return (1 + ft_numdig(n / 10));
}

char	*ft_itoa(int n)
{
	char	*num;
	int		num_dig;
	int		i;
	int		signal;

	signal = n;
	num_dig = ft_numdig(n) + 1 + (n < 0);
	num = (char *)malloc(sizeof(char) * num_dig);
	if (!num)
		return (NULL);
	num[num_dig - 1] = '\0';
	i = num_dig - 2;
	while (i > -1)
	{
		num[i] = ((n % 10) * ((n > 0) - (n < 0))) + 48;
		n /= 10;
		i--;
	}
	if (signal < 0)
		num[0] = '-';
	return (num);
}

int	printerror(char *str, int fd)
{
	if (str && *str)
		prints(str, fd, NULL);
	if (this()->env)
		free_matrix(this()->env);
	rmlist(&this()->cmds);
	exit ((unsigned char)this()->status);
}
