/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extend_outfile.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bince < bince@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 06:47:14 by bince             #+#    #+#             */
/*   Updated: 2024/08/13 06:47:16 by bince            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*extend_outfile(t_nns *nns, int i, int j, int k)
{
	int		extended;
	char	*wo_quote;

	if (nns->newstr[k] == -2 || nns->newstr[k] == '>')
		extended = 2;
	else
		extended = 1;
	wo_quote = cut_str(nns->newstr, i, j, extended);
	if (!wo_quote)
		return (NULL);
	if (extended == 2)
	{
		if (nns->newstr[k] == -2)
			wo_quote[0] = 'x';
		else
			wo_quote[0] = '0';
	}
	return (wo_quote);
}
