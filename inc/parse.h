/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gade-alm <gade-alm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 11:52:53 by gade-alm          #+#    #+#             */
/*   Updated: 2023/04/19 11:53:16 by gade-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

int		count_args(char *str);
int		char_delim(char *str, int i, char *delim);
char	*ft_word(const char *s, char *word, int len);
char	**ft_split(char *str);
int		check_single_quote(char *str, int i, char quote);
int		check_string(char *str);
int		check_strings_2(char *str);
int		check_redir(char *str, int i, char redir);
int		check_redirection(char *str, int i, char c);
int		token_helper(char *str, char c, int i);
int		check_heredocs(char *str, int i);
int		token_len(char *str);
char	**handle_commands(char *str, char **envp, int i);
void	cmds_split(char **arg);

#endif