/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_handler_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bince < bince@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 13:00:12 by bince             #+#    #+#             */
/*   Updated: 2024/08/13 13:00:35 by bince            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	*write_quote_indexes(char *str)
{
	int			i;
	t_vector2	v2;
	int			*quote_indexes;
	int			quote_count;

	i = 0;
	quote_count = count_quotes(str);
	quote_indexes = malloc(sizeof(int) * (quote_count * 2 + 1));
	if (!quote_indexes)
		return (NULL);
	v2 = quote_handler(str, 0);
	while (i < quote_count * 2)
	{
		quote_indexes[i] = v2.i;
		i++;
		quote_indexes[i] = v2.j;
		i++;
		v2 = quote_handler(str, v2.i + 1);
	}
	quote_indexes[i] = -1;
	return (quote_indexes);
}

int	is_quote_index(int i, int *quote_indexes)
{
	int	j;

	j = 0;
	while (quote_indexes[j] != -1)
	{
		if (quote_indexes[j] == i)
			return (1);
		j++;
	}
	return (0);
}
