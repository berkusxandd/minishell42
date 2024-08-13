/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bince < bince@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 06:44:34 by bince             #+#    #+#             */
/*   Updated: 2024/08/13 06:44:36 by bince            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**error_1(char **tokens, t_nns *nns)
{
	free_tab(tokens);
	free_nns(nns);
	return (NULL);
}

char	**error_2(char **tokens)
{
	free_tab(tokens);
	return (NULL);
}
