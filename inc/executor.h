/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gade-alm <gade-alm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 08:21:06 by grebin            #+#    #+#             */
/*   Updated: 2023/05/03 10:44:18 by gade-alm         ###   ########.fr       */
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
void	prep_fd(t_cmd *cmd);
int		heredocs(char *delim);

#endif
