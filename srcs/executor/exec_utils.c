/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 14:58:52 by grebin            #+#    #+#             */
/*   Updated: 2023/05/04 16:02:38 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/executor.h"

void	close_fds(void)
{
	if (this()->cmds->output != 1)
		close(this()->cmds->output);
	if (this()->cmds->input != 0)
		close(this()->cmds->input);
}

void	update_status(t_shell *shell)
{
	int	status;

	if (WIFEXITED(shell->status))
	{
		status = WEXITSTATUS(shell->status);
		shell->status = status;
	}
}

void	waiting(void)
{
	while (this()->cmdsindex > 0)
	{
		this()->cmdsindex--;
		wait(&this()->status);
	}
	update_status(this());
}

void	forks(void)
{
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
			exit(this()->status = cmd_handler(this()->env, \
			this()->cmds->input, this()->cmds->output));
	}
}

void	executor(t_cmd *cmd)
{
	while (this()->cmds)
	{
		if (!this()->cmds->cmd)
		{
			close_fds();
			rmnode(&this()->cmds);
			if (!this()->cmds)
				break ;
		}
		if (is_builtin() && this()->cmdsindex == 1)
		{
			builtins(cmd);
			return ;
		}
		forks();
		close_fds();
		rmnode(&this()->cmds);
	}
	waiting();
}
