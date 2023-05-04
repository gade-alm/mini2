/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebin <grebin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 08:21:06 by grebin            #+#    #+#             */
/*   Updated: 2023/05/04 15:34:43 by grebin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>

# include <readline/readline.h>
# include <readline/history.h>

# include "strings.h"
# include "env.h"
# include "allocation.h"
# include "builtins.h"
# include "minishell.h"
# include "struct.h"
# include "lists.h"

//SO PRA FECHAR O FD
typedef struct s_sig{
	int		value[2];
	int		check;
}t_sig;

t_sig	*sigcall(void);
void	executor(t_cmd *cmd);
void	builtins(t_cmd *cmd);
void	heredocs_ctrl_d(char *temp, char *delim);
void	child_clean(t_cmd *cmd);
void	prep_fd(t_cmd *cmd);
int		heredocs(char *delim);

int		is_builtin(void);
int		cmd_handler(char **env, int input, int output);

#endif
