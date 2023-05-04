/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebin <grebin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 10:12:13 by gabriel           #+#    #+#             */
/*   Updated: 2023/05/04 15:13:45 by grebin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*find_var(char *str, int i)
{
	char	*temp;
	int		j;

	j = 0;
	if (str[i + 1] == '?')
		return ("status");
	while (str[++i] && str[i] != ' ' && str[i] != '\t' \
	&& str[i] != '"' && str[i] != '$')
		j++;
	temp = malloc(sizeof(char) * (j + 1));
	if (!temp)
		return (NULL);
	temp[j] = '\0';
	while (--j > -1)
		temp[j] = str[--i];
	return (temp);
}

int	expander_len(char *str)
{
	int	i;
	int	len;

	len = 0;
	i = -1;
	if (!str)
		return (0);
	while (str[++i] && str[i] != '$')
		len++;
	while (str[i] && (str[i] != ' ' && str[i] != '\t' \
	&& str[i] != '"' && str[i] != '\'' && str[i] != '$'))
		i++;
	while (str[i++])
		len++;
	return (len);
}

char	*env_value(char *key, char **env, char *str, int x)
{
	int		i;
	int		j;
	char	*value;
	int		len;

	i = -1;
	if (str[x + 1] == '?' && (!ft_strncmp("status", key, 7)))
		return (ft_itoa(this()->status));
	while (env[++i] && !verify_var(key, env[i]))
		;
	len = -1;
	while (env[i] && env[i][++len] && env[i][len] != '=')
		;
	len += (env[i] && env[i][len] == '=');
	value = malloc(sizeof(char) * (ft_strlen(env[i]) * len) + 1);
	if (!value)
		return (NULL);
	j = 0;
	while (env[i] && env[i][len - 1])
		value[j++] = env[i][len++];
	value[j] = '\0';
	free (key);
	return (value);
}

char	*join_expander(char *str, char *value, int x)
{
	int		i;
	int		j;
	int		k;
	char	*joint;

	joint = malloc(sizeof(char) * (expander_len(str) + expander_len(value) \
	+ 1));
	if (!joint)
		return (NULL);
	i = -1;
	k = -1;
	j = -1;
	while (str[++i] && (str[i] != '$' || i < x))
		joint[++k] = str[i];
	while (value[++j])
		joint[++k] = value[j];
	while (str[++i] && str[i] != ' ' && str[i] != '\t' && str[i] \
	!= '"' && str[i] != '\'' && str[i] != '$')
		;
	while (str[i])
		joint[++k] = str[i++];
	joint[++k] = 0;
	return (joint);
}

char	*expand_var(char *str, char **env, int i)
{
	char	*key;
	char	*value;
	char	*joint;

	key = find_var(str, i);
	value = env_value(key, env, str, i);
	if (!value)
		return (0);
	joint = join_expander(str, value, i);
	free (value);
	free (str);
	return (joint);
}
