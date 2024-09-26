/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_array.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bince < bince@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 13:11:48 by bince             #+#    #+#             */
/*   Updated: 2024/08/13 17:15:56 by bince            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_tokens(char *input, char token)
{
	int	i;
	int	count;
	int	quote_type;

	quote_type = 0;
	count = 0;
	i = 0;
	while (input[i])
	{
		quote_type = quote_check(input[i], quote_type);
		if (is_cur_token(input[i], token) != 0 && quote_type == 0)
			count++;
		i++;
	}
	return (count);
}

char	*put_tokens_in_array(t_nns **nns, int i, char **tokens)
{
	tokens[i] = ft_strdup((*nns)->name);
	free((*nns)->name);
	(*nns)->name = NULL;
	return (tokens[i]);
}

char	**calloc_token_array(t_nns **nns, char token, int *token_count)
{
	char	**tokens;

	*token_count = count_tokens((*nns)->newstr, token);
	tokens = ft_calloc(sizeof(char *), (*token_count + 1));
	return (tokens);
}
