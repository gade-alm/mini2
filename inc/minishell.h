/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gade-alm <gade-alm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 10:53:03 by gabriel           #+#    #+#             */
/*   Updated: 2023/05/04 12:42:43 by gade-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include "parse.h"
# include "lists.h"
# include "allocation.h"
# include "builtins.h"
# include "struct.h"
# include "executor.h"
# include "env.h"
# include "struct.h"
# include "strings.h"

//EXPANDER AREA
char	*expand_var(char *str, char **env, int i);
int		verify_var(char *str, char *env);
char	*find_var(char *str, int i);
int		expander_len(char *str);
char	*env_value(char *key, char **env, char *str, int x);
char	*remove_quotes(char *str, int i, int j);
char	*remove_single_quotes(char *str, int i, int j);
char	*remove_double_quotes(char *str, int i, int j);

#endif
