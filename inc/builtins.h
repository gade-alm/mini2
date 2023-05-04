/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gade-alm <gade-alm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 17:07:54 by grebin            #+#    #+#             */
/*   Updated: 2023/05/04 12:42:55 by gade-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "strings.h"
# include "env.h"
# include "allocation.h"
# include "struct.h"
# include "lists.h"

int		pwd(int output);
int		env(t_cmd *cmd, char **env, int output);
int		echo(t_cmd *cmd, int output);
int		unset(t_cmd *cmd);
int		export(t_cmd *cmd, char **env);//AJEITAR O NOME
int		cd(t_cmd *cmd, char **env);
void	change_pwd(void);
int		add_pwd(void);
int		exit_prog(t_cmd *cmd, int status);
int		cd_home(char **env, t_cmd *node);
int		print_export(char **env);

#endif
