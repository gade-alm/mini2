/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 10:53:03 by gabriel           #+#    #+#             */
/*   Updated: 2023/04/16 14:26:16 by gabriel          ###   ########.fr       */
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
# include "lists.h"
# include "allocation.h"
# include "builtins.h"
# include "struct.h"
# include "executor.h"
# include "env.h"
# include "struct.h"
# include "strings.h"

//UTILS AREA
int		ft_strlen(const char *str);
int		ft_strcmp(const char *s1, const char *s2);
int		is_space(char *str, int i);
char	*ft_strrchr(const char *s, int c);
char	*ft_strchr(const char *s, int c);
void	sig_handler(int signal);
char	**ft_realloc(char **matrix, int change);

//STRINGS AREA
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char const *s1, char const *s2);

//PARSE AREA
int		count_args(char *str);
int		char_delim(char *str, int i, char *delim);
char	*ft_word(const char *s, char *word, int len);
char	**ft_split(char *str);
int		check_single_quote(char *str, int i);
int		check_double_quote(char *str, int i);
int		check_string(char *str);
int		check_pipe(char *str, int i);
int		check_redirection(char *str, int i, char c);
int		token_helper(char *str, char c, int i);
int		token_len(char *str);
char	**handle_commands(char *str, char **envp, int i);
void	cmds_split(char **arg);

//EXPANDER AREA
char	*expand_var(char *str, char **env, int i);
int		strcharlen(char *str, char c);
char	*print_env(char *env, int i);
int		verify_var(char *str, char *env);
char	*find_var(char *str, int i);
int		expander_len(char *str);
char	*env_value(char *key, char **env, char *str, int x);
char	*remove_quotes(char *str, int i, int j);
char	*remove_single_quotes(char *str, int i, int j);
char	*remove_double_quotes(char *str, int i, int j);


#endif
