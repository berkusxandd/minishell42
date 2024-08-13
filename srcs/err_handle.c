/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bince < bince@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 06:44:34 by bince             #+#    #+#             */
/*   Updated: 2024/08/13 10:38:05 by bince            ###   ########.fr       */
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

void error_empty_pipe(t_data *core)
{
	core->status = 1;
	ft_putstr_fd("parse error near |.\n", 2);
}

void error_pipeline_malloc(t_data *core)
{
	ft_putstr_fd("pipeline malloc error\n", 1);
	free_all_pipelines(core->all_pipes);
}
