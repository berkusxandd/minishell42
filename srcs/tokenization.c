/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bince < bince@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 13:11:34 by bince             #+#    #+#             */
/*   Updated: 2024/08/13 13:11:34 by bince            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_nns(t_nns *nns)
{
	if (nns)
	{
		free(nns->name);
		free(nns->newstr);
		free(nns);
	}
}

int	put_contents_to_nns(t_nns *nns, int i, int j, int k)
{
	char	*tmp;
	char	*wo_quote;

	wo_quote = extend_outfile(nns, i, j, k);
	if (!wo_quote)
		return (0);
	nns->name = quote_parser(wo_quote);
	if (!nns->name)
	{
		free_nns(nns);
		return (0);
	}
	tmp = nns->newstr;
	nns->newstr = delete_part(tmp, i, j, k);
	free(tmp);
	if (!nns->newstr)
	{
		free_nns(nns);
		return (0);
	}
	return (1);
}

t_nns	*find_token(t_nns *nns, char token)
{
	int	quote_type;
	int	i;
	int	j;
	int	k;

	i = 0;
	quote_type = 0;
	while (nns->newstr[i])
	{
		quote_type = quote_check(nns->newstr[i], quote_type);
		if (is_cur_token(nns->newstr[i], token) != 0 && quote_type == 0)
		{
			k = i++;
			i = space_skip(nns, &quote_type, i, k);
			index_arranger(nns, &i, &j, quote_type);
			if (i != j)
			{
				if (put_contents_to_nns(nns, i, j, k) == 0)
					return (NULL);
			}
			return (nns);
		}
		i++;
	}
	return (nns);
}

t_nns	*gen_token(t_nns *nns_old, char token)
{
	t_nns	*nns;
	char	*newstr;

	newstr = ft_strdup(nns_old->newstr);
	if (!newstr)
		return (NULL);
	free(nns_old->newstr);
	free(nns_old);
	if (!newstr)
		return (NULL);
	nns = nns_init(newstr);
	free(newstr);
	if (!nns)
		return (NULL);
	nns = find_token(nns, token);
	return (nns);
}

char	**tokenization(t_nns **nns, char token)
{
	int		token_count;
	int		i;
	char	**tokens;

	i = 0;
	tokens = calloc_token_array(nns, token, &token_count);
	if (!tokens)
		return (NULL);
	while (i < token_count)
	{
		*nns = gen_token(*nns, token);
		if (!(*nns))
			return (error_2(tokens));
		if ((*nns)->name)
		{
			tokens[i] = put_tokens_in_array(nns, i, tokens);
			if (!tokens[i])
				return (error_1(tokens, (*nns)));
		}
		else
			tokens[i] = NULL;
		i++;
	}
	tokens[i] = NULL;
	return (tokens);
}
