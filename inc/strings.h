/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gade-alm <gade-alm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 17:43:15 by grebin            #+#    #+#             */
/*   Updated: 2023/04/11 12:16:29 by gade-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRINGS_H
# define STRINGS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

int			ft_strlen(const char *s);
char		*ft_strdup(const char *s1);
int			prints(char *str, char fd);
char		*ft_strjoin(char const *s1, char const *s2);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
long		ft_atoi(char *s);
char		*ft_strncpy(char *str, char *temp, int size);
char		*ft_itoa(int n);
int			printerror(char *str);

#endif