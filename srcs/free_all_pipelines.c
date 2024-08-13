/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all_pipelines.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bince < bince@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 06:47:21 by bince             #+#    #+#             */
/*   Updated: 2024/08/13 12:52:06 by bince            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_pipeline_2(t_pipeline *pipeline)
{
	int	i;

	i = 0;
	if (pipeline->outfiles)
	{
		while (pipeline->outfiles[i])
			free(pipeline->outfiles[i++]);
		free(pipeline->outfiles);
	}
	i = 0;
	if (pipeline->here_docs)
	{
		while (pipeline->here_docs[i])
			free(pipeline->here_docs[i++]);
		free(pipeline->here_docs);
	}
	if (pipeline->here_filename)
		free(pipeline->here_filename);
}

void	free_pipeline(t_pipeline *pipeline)
{
	int	i;

	i = 0;
	if (pipeline->cmd)
	{
		while (pipeline->cmd[i])
			free(pipeline->cmd[i++]);
		free(pipeline->cmd);
	}
	i = 0;
	if (pipeline->infiles)
	{
		while (pipeline->infiles[i])
			free(pipeline->infiles[i++]);
		free(pipeline->infiles);
	}
	free_pipeline_2(pipeline);
	free(pipeline);
}

void	free_all_pipelines(t_all_pipelines *all_pipelines)
{
	int	i;

	i = 0;
	if (!all_pipelines)
		return ;
	if (all_pipelines->pipelines)
	{
		while (all_pipelines->pipelines[i] != NULL)
		{
			free_pipeline(all_pipelines->pipelines[i]);
			i++;
		}
		free(all_pipelines->pipelines);
	}
	free(all_pipelines);
}
