/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bince < bince@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 06:47:58 by bince             #+#    #+#             */
/*   Updated: 2024/08/13 17:08:14 by bince            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_nns	*nns_init(char *input)
{
	t_nns	*nns;

	nns = malloc(sizeof(t_nns));
	if (nns == NULL)
		return (NULL);
	nns->name = NULL;
	nns->newstr = ft_strdup(input);
	if (!nns->newstr)
	{
		free(nns);
		return (NULL);
	}
	return (nns);
}

t_pipeline	*pipeline_init(void)
{
	t_pipeline	*pipeline;

	pipeline = malloc(sizeof(t_pipeline));
	if (pipeline == NULL)
		return (NULL);
	pipeline->cmd = NULL;
	pipeline->infiles = NULL;
	pipeline->outfiles = NULL;
	pipeline->here_docs = NULL;
	pipeline->here_filename = NULL;
	pipeline->infile_fd = 0;
	pipeline->outfile_fd = 1;
	return (pipeline);
}
