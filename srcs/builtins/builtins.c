/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gade-alm <gade-alm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 17:02:48 by grebin            #+#    #+#             */
/*   Updated: 2023/04/13 11:29:51 by gade-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/builtins.h"

int	pwd(int output)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		perror("pwd");
		return (1);
	}
	prints(pwd, output);
	free(pwd);
	return (0);
}

int	cd(t_cmd *cmd, char **env)
{	
	if (!cmd->cmd[1])
		return (1);
	if (!check_var("PWD=", env, 4))
		add_pwd();
	if (cmd->cmd[2])
	{
		prints("too many arguments", 2);
		return (1);
	}	
	if (chdir(cmd->cmd[1]))
	{
		perror("chdir");
		return (1);
	}
	change_pwd();
	return (0);
}


int	env(t_cmd *cmd, char **env, int output)
{
	int	i;

	if (cmd->cmd[1])
		return (1);
	if (!env)
	{
		prints("Env doesn't exist", 2);
		return (1);
	}
	i = -1;
	while (env[++i])
		prints(env[i], output);
	return (0);
}

int	echo(t_cmd *cmd, int output)
{
	int	i;

	i = 0 + (ft_strncmp("-n", cmd->cmd[1], 3) == 0);
	while (cmd->cmd[++i])
	{
		prints(cmd->cmd[i], output);
		if (cmd->cmd[i + 1])
			write(output, " ", 1);
	}
	if (ft_strncmp("-n", cmd->cmd[1], 3))
		write(output, "\n", 1);
	return (0);
}

int	unset(t_cmd *cmd)
{
	int	i;

	i = -1;
	if (!cmd->cmd[1])
		return (1);
	while (this()->env[++i])
	{
		if (ft_strncmp(cmd->cmd[1], this()->env[i], \
		ft_strlen(cmd->cmd[1])) == 0)
		{
			this()->env = rm_var(cmd->cmd[1], \
			this()->env, ft_strlen(cmd->cmd[1]));
			return (1);	
		}
	}
	return (0);
}

