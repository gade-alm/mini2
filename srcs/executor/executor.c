/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebin <grebin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 08:20:18 by grebin            #+#    #+#             */
/*   Updated: 2023/05/02 11:22:05 by grebin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/executor.h"

void	child_clean(t_cmd *cmd)
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

void	builtins(t_cmd *cmd)
{
	if (ft_strncmp("cd", cmd->path, 3) == 0)
		(this())->status = cd(cmd, this()->env);
	else if (ft_strncmp("echo", cmd->path, 5) == 0)
		(this())->status = echo(cmd, cmd->output);
	else if (ft_strncmp("unset", cmd->path, 6) == 0)
		(this())->status = unset(cmd);
	else if (ft_strncmp("export", cmd->path, 7) == 0)
		(this())->status = export(cmd, this()->env);
	else if (ft_strncmp("env",cmd->path, 4) == 0)
		(this())->status = env(cmd, this()->env, cmd->output);
	else if (ft_strncmp("pwd", cmd->path, 4) == 0)
		this()->status = pwd(cmd->output);
	else if (ft_strncmp("exit", cmd->path, 5) == 0)
		(this())->status = exit_prog(cmd, this()->status);
	child_clean(this()->cmds);
	rmnode(&this()->cmds);
}

void	child(char **env, int input, int output)
{
	if (input != 0)
	{
		if (dup2(input, STDIN_FILENO) == -1)
			perror("dup1");
		close(input);
	}
	if (output != 1)
	{
		if (dup2(output, STDOUT_FILENO) == -1)
			perror("dup2");
		close(output);
	}
	if (execve(this()->cmds->path, this()->cmds->cmd, env) == -1)
	{
		rmlist(&this()->cmds);
		free_matrix(env);
		perror("execve");
	}
}

int	cmd_handler(char **env, int input, int output)
{
	if (set_path(this()->cmds) == -1)
	{
		prints("Command not found:", 2, this()->cmds->cmd[0]);
		return (127);
	}
	child_clean(this()->cmds->next);
	child(env, input, output);
	rmnode(&this()->cmds);
	return (0);
}

int	is_builtin(void)
{
	return (ft_strncmp("cd", this()->cmds->cmd[0], 3) == 0 || \
	ft_strncmp("echo", (this())->cmds->cmd[0], 5) == 0 || \
	ft_strncmp("exit", this()->cmds->cmd[0], 5) == 0 \
	|| ft_strncmp("unset", this()->cmds->cmd[0], 6) == 0 || ft_strncmp("pwd", \
	this()->cmds->cmd[0], 4) == 0 || ft_strncmp("export", \
	this()->cmds->cmd[0], 7) == 0 || \
	ft_strncmp("env", this()->cmds->cmd[0], 4) == 0);
}

void	executor(t_cmd *cmd)
{
	// printlist(this()->cmds);
	while (this()->cmds)
	{
		if (!this()->cmds->cmd)
		{
			if (this()->cmds->output != 1)
				close(this()->cmds->output);
			if (this()->cmds->input != 0)
				close(this()->cmds->input);
			rmnode(&this()->cmds);
			if (!this()->cmds)
				break ;
		}
		printf("%i\n", this()->cmdsindex);
		if (is_builtin() && this()->cmdsindex == 1)
		{
			builtins(cmd);
			return ;
		}
		this()->cmds->pid = fork();
		if (this()->cmds->pid == -1)
			prints("Error creating second fork", 2, this()->cmds->cmd[0]);
		if (this()->cmds->pid == 0)
		{
			if (is_builtin())
			{
				builtins(this()->cmds);
				exit(this()->status);
			}
			else
				exit(this()->status = cmd_handler(this()->env, this()->cmds->input, this()->cmds->output));
		}
		if (this()->cmds->output != 1)
			close(this()->cmds->output);
		if (this()->cmds->input != 0)
			close(this()->cmds->input);
		rmnode(&this()->cmds);
	}
	while (this()->cmdsindex > 0)
	{
		this()->cmdsindex--;
		wait(NULL);
	}
}
