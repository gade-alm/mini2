/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebin <grebin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 16:22:25 by grebin            #+#    #+#             */
/*   Updated: 2023/04/24 08:33:44 by grebin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
//EXIT PROG ON RETURN NULL
char	**alloc_matrix(char **matrix, int change)
{
	int		i;
	char	**new;

	i = -1;
	if (!matrix)
		return (NULL);
	while (matrix[++i])
		;
	new = malloc(sizeof(char *) * (i + 1 + change));
	if (!new)
		return (NULL);
	return (new);
}

void	free_matrix(char **matrix)
{
	int	i;

	i = -1;
	if (!matrix)
		return ;
	while (matrix[++i])
		free(matrix[i]);
	free(matrix);
}

//EXIT PROG ON RETURN NULL
char	*alloc_string(char *string)
{
	int		i;
	int		j;
	char	*new;

	i = -1;
	j = -1;
	if (!string && !*string)
		return (NULL);
	while (string[++i])
		;
	new = malloc(sizeof(char) * (i + 1));
	if (!new)
		return (NULL);
	while (string[++j])
		new[j] = string[j];
	new[j] = 0;
	return (new);
}

char	**ft_realloc(char **matrix, int change)
{
	int		i;
	char	**new;

	i = -1 + (!matrix);
	while (matrix && matrix[++i])
		;
	new = malloc(sizeof(char *) * ((i + 1) + change));
	if (!new)
		return (NULL);
	return (new);
}
