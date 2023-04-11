/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebin <grebin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 08:20:18 by grebin            #+#    #+#             */
/*   Updated: 2023/04/04 18:20:30 by grebin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/executor.h"


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
		exit_prog(cmd, this()->status);
	rmnode(&this()->cmds);
}

void	child(char **env, int input, int output)
{
	if(input != 0)
			if (dup2(input, STDIN_FILENO) == -1)
				prints("Error on first Dup2", 2);
	if(output != 1)
		if (dup2(output, STDOUT_FILENO) == -1)
			prints("Error on second Dup2", 2);
	if (execve(this()->cmds->path, this()->cmds->cmd, env) == -1)
		prints("Error executing command", 2);
	close(input);
	close(output);
	
}

int cmd_handler(char **env, int input, int output)
{
	this()->cmds->pid = fork();
	if (this()->cmds->pid == -1)
		prints("Error creating second fork", 2);
	if (this()->cmds->pid == 0)
	{
		if(input != 0)
			if (dup2(input, STDIN_FILENO) == -1)
				prints("Error on first Dup2", 2);
		if(output != 1)
			if (dup2(output, STDOUT_FILENO) == -1)
				prints("Error on second Dup2", 2);
		if (execve(this()->cmds->path, this()->cmds->cmd, env) == -1)
			prints("Error executing command", 2);
		close(input);
		close(output);
	}
		//child(env, input, output);
	if (output != 1)
		close(output);
	if (input != 0)
		close(input);
	//printf("exit\n");
	rmnode(&this()->cmds);
	wait(NULL);
	return (0);
}

void executor(t_cmd *cmd)
{
	if (ft_strncmp("cd", cmd->cmd[0], 3) == 0 || ft_strncmp("echo", \
	cmd->cmd[0], 5) == 0 || ft_strncmp("exit", cmd->cmd[0], 5) == 0 \
	|| ft_strncmp("unset", cmd->cmd[0], 6) == 0 || ft_strncmp("pwd", \
	cmd->cmd[0], 4) == 0 || ft_strncmp("export", cmd->cmd[0], 7) == 0 \
	|| ft_strncmp("env", cmd->cmd[0], 4) == 0)
		builtins(cmd);
	else
		cmd_handler(this()->env, cmd->input, cmd->output);
	wait(NULL);
}
