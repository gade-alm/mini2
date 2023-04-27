/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebin <grebin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 17:48:52 by grebin            #+#    #+#             */
/*   Updated: 2023/04/24 08:31:36 by grebin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/builtins.h"

int	export(t_cmd *cmd, char **env)
{
	int		i;
	char	*temp;

	i = -1;
	if (!cmd->cmd[1])
		return (1); // print declare -x
	temp = ft_strdup(cmd->cmd[1]);
	if (!temp)
		printerror("malloc error", 2);
	while (temp[++i] != '=' && temp[i])
		;
	if (temp[i] != '=' || !ft_strlen(temp + i + 1))
	{
		free(temp);
		return (0);
	}
	if (check_var(temp, env, ++i))
		(this())->env = change_var(temp, temp, env, i);
	else
		(this())->env = add_var(temp, env);
	return (0);
}

int	add_pwd(void)
{
	char	*pwd;
	char	*temp;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (prints("PWD not found", 2, NULL));
	temp = ft_strjoin("PWD=", pwd);
	(this())->env = add_var(temp, this()->env);
	free(pwd);
	return (0);
}

void	change_pwd(void)
{
	char	*old;
	char	*temp;
	char	*pwd;

	temp = ft_strdup(check_var("PWD=", this()->env, 3));
	old = ft_strjoin("OLD", temp);
	free(temp);
	if (!check_var("OLDPWD=", this()->env, 7))
		(this())->env = add_var(old, this()->env);
	else
		(this())->env = change_var(check_var("OLDPWD=", this()->env, 7), \
		old, this()->env, 7);
	temp = getcwd(NULL, 0);
	pwd = ft_strjoin("PWD=", temp);
	(this())->env = change_var(check_var("PWD=", this()->env, 4), \
	pwd, this()->env, 4);
	free(temp);
}

int	is_nbr(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] < '0' && str[i] > '9')
			return (1);
	}
	return (0);
}

int	exit_prog(t_cmd *cmd, int status)
{
	int	argc;

	argc = 0;
	prints("exit", 1, NULL);
	while (cmd->cmd[++argc])
		;
	if (cmd->cmd[1] && is_nbr(cmd->cmd[1]))
	{
		prints("numeric argument required\n", 2, "exit");
		status = 2;
	}
	else if (argc > 2)
	{
		prints("too many args\n", 2, "exit");
		return (1);
	}
	else if (cmd->cmd[1])
		status = ft_atoi(cmd->cmd[1]);
	rmlist(&this()->cmds);
	free_matrix(this()->env);
	clear_history();
	exit (status);
}
