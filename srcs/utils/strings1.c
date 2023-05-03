/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebin <grebin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 13:39:06 by grebin            #+#    #+#             */
/*   Updated: 2023/05/03 12:38:10 by grebin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

long	ft_atoi(char *s)
{
	int			i;
	int			signal;
	long long	conv;

	i = 0;
	signal = 1;
	conv = 0;
	while (s[i] == 32 || (s[i] > 8 && s[i] < 14))
		i++;
	if (s [i] == '-' || s[i] == '+')
	{
		if (s[i] == '-')
			signal *= -1;
		i++;
	}
	while (s[i] >= '0' && s[i] <= '9')
	{
		conv = (conv * 10 + (signal * (s[i] - '0')));
			i++;
		if (conv > 2147483647)
			return (-1);
		if (conv < -2147483648)
			return (0);
	}
	return (conv);
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
