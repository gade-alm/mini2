/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 08:21:06 by grebin            #+#    #+#             */
/*   Updated: 2023/04/16 13:32:38 by gabriel          ###   ########.fr       */
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
# include "struct.h"
# include "lists.h"

void	executor(t_cmd *cmd);
void	builtins(t_cmd *cmd);
void	prep_fd(t_cmd *cmd);
int		heredocs(char *delim);

#endif
