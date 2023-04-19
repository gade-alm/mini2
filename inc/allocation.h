/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocation.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gade-alm <gade-alm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 16:28:04 by grebin            #+#    #+#             */
/*   Updated: 2023/04/19 11:57:21 by gade-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALLOCATION_H
# define ALLOCATION_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

char	**alloc_matrix(char **matrix, int change);
void	free_matrix(char **matrix);
char	*alloc_string(char *string);
char	**ft_realloc(char **matrix, int change);

#endif