/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gade-alm <gade-alm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 08:20:18 by grebin            #+#    #+#             */
/*   Updated: 2023/04/13 12:59:16 by gade-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/executor.h"

void child_clean(t_cmd *cmd)
{
	while (cmd)
	{
		if (cmd->output != 1)
			close(cmd->output);
		if (cmd->input != 0)
			close(cmd->input);
		cmd = cmd->next;
	}
}

void builtins(t_cmd *cmd)
{
	if (ft_strncmp("cd", cmd->cmd[0], 3) == 0)
		this()->status = cd(cmd, this()->env);
	if (ft_strncmp("echo", cmd->cmd[0], 5) == 0)
		this()->status = echo(cmd, cmd->output);
	if (ft_strncmp("unset", cmd->cmd[0], 6) == 0)
		this()->status = unset(cmd);
	if (ft_strncmp("export", cmd->cmd[0], 7) == 0)
		this()->status = export(cmd, this()->env);
	if (ft_strncmp("env", cmd->cmd[0], 4) == 0)
		this()->status = env(cmd, this()->env, cmd->output);
	if (ft_strncmp("pwd", cmd->cmd[0], 4) == 0)
		this()->status = pwd(cmd->output);
	if (ft_strncmp("exit", cmd->cmd[0], 3) == 0)
		this()->status = exit_prog(cmd, this()->status);
	rmnode(&this()->cmds);
}

void	child(char **env, int input, int output)
{
	if(input != 0)
	{
		if (dup2(input, STDIN_FILENO) == -1)
			prints("Error on first Dup2", 2);
		close(input);
	}
	if(output != 1)
	{
		if (dup2(output, STDOUT_FILENO) == -1)
			prints("Error on second Dup2", 2);
		close(output);
	}
	if (execve(this()->cmds->path, this()->cmds->cmd, env) == -1)
	{
		rmlist(&this()->cmds);
		prints("Error executing command", 2);
	}
	
}

int cmd_handler(char **env, int input, int output)
{
	set_path(this()->cmds); // not found status 127 e adicionar msg de erro
	this()->cmds->pid = fork();
	if (this()->cmds->pid == -1)
		prints("Error creating second fork", 2);
	if (this()->cmds->pid == 0)
	{
		child_clean(this()->cmds->next);
		child(env, input, output);
	}
	if (output != 1)
		close(output);
	if (input != 0)
		close(input);
	rmnode(&this()->cmds);
	return (0);
}

void executor(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (this()->cmds)
	{
		if (ft_strncmp("cd",this()->cmds->cmd[0], 3) == 0 || ft_strncmp("echo", \
		this()->cmds->cmd[0], 5) == 0 || ft_strncmp("exit",this()->cmds->cmd[0], 5) == 0 \
		|| ft_strncmp("unset", this()->cmds->cmd[0], 6) == 0 || ft_strncmp("pwd", \
		this()->cmds->cmd[0], 4) == 0 || ft_strncmp("export", this()->cmds->cmd[0], 7) == 0 \
		|| ft_strncmp("env", this()->cmds->cmd[0], 4) == 0)
			builtins(cmd);
		else
			this()->status = cmd_handler(this()->env, this()->cmds->input, this()->cmds->output);
		i++;
	}
	while (i-- > 0)
		wait(NULL);
}
