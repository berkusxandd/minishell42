/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bince < bince@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 12:59:43 by bince             #+#    #+#             */
/*   Updated: 2024/08/13 12:59:56 by bince            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	quote_check(char c, int quote_type)
{
	if (c == 39 && quote_type == 0)
		return (1);
	else if (c == 39 && quote_type == 1)
		return (0);
	else if (c == 34 && quote_type == 0)
		return (2);
	else if (c == 34 && quote_type == 2)
		return (0);
	else
		return (quote_type);
}

t_vector2	quote_handler(char *str, int i)
{
	t_vector2	v2;
	int			quote_type;
	int			old_quote_type;

	v2.i = i;
	v2.j = i;
	quote_type = 0;
	while (str[v2.i])
	{
		old_quote_type = quote_type;
		quote_type = quote_check(str[v2.i], quote_type);
		if (old_quote_type != quote_type && quote_type != 0)
			v2.j = v2.i;
		if (old_quote_type != quote_type && quote_type == 0)
		{
			return (v2);
		}
		v2.i++;
	}
	return (v2);
}

int	count_quotes(char *str)
{
	int	quote_type;
	int	old_quote_type;
	int	quote_count;
	int	i;

	i = 0;
	quote_type = 0;
	quote_count = 0;
	while (str[i])
	{
		old_quote_type = quote_type;
		quote_type = quote_check(str[i], quote_type);
		if (old_quote_type != quote_type && quote_type == 0)
			quote_count++;
		i++;
	}
	return (quote_count);
}

char	*generate_str_wo_quotes(char *str, int *quote_indexes)
{
	int		i;
	int		j;
	char	*parsed_str;
	int		quote_count;

	quote_count = count_quotes(str);
	parsed_str = malloc(sizeof(char) * (ft_strlen(str) + 1) - (quote_count
				* 2));
	if (!parsed_str)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (is_quote_index(i, quote_indexes) == 0)
		{
			parsed_str[j] = str[i];
			j++;
		}
		i++;
	}
	parsed_str[j] = '\0';
	free(quote_indexes);
	return (parsed_str);
}

char	*quote_parser(char *str)
{
	int		*quote_indexes;
	char	*parsed_str;

	quote_indexes = write_quote_indexes(str);
	if (!quote_indexes)
		return (NULL);
	parsed_str = generate_str_wo_quotes(str, quote_indexes);
	free(str);
	if (!parsed_str)
		free(quote_indexes);
	return (parsed_str);
}
