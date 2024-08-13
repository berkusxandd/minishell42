/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_ofiles.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bince < bince@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 12:37:44 by bince             #+#    #+#             */
/*   Updated: 2024/08/13 12:38:02 by bince            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	open_outfile_0(t_pipeline *node, char *filepath, int fd, int i)
{
	node->outfiles[i]++;
	filepath = NULL;
	fd = -1;
	filepath = get_pathfile(node->outfiles[i]);
	node->outfiles[i]--;
	if (access(filepath, W_OK) == 0 || access(filepath, F_OK) == -1)
	{
		fd = open(filepath, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		if (node->outfiles[i + 1] == NULL && fd != -1)
			node->outfile_fd = fd;
		else if (fd != -1)
			close(fd);
		else if (fd == -1)
			return (free(filepath), EXIT_FAILURE);
	}
	else
		return (free(filepath), EXIT_FAILURE);
	free(filepath);
	return (EXIT_SUCCESS);
}

int	open_outfile_x(t_pipeline *node, char *filepath, int fd, int i)
{
	node->outfiles[i]++;
	filepath = NULL;
	fd = -1;
	filepath = get_pathfile(node->outfiles[i]);
	node->outfiles[i]--;
	if (access(filepath, W_OK) == 0 || access(filepath, F_OK) == -1)
	{
		fd = open(filepath, O_WRONLY | O_CREAT | O_APPEND, 0666);
		if (node->outfiles[i + 1] == NULL && fd != -1)
			node->outfile_fd = fd;
		else if (fd != -1)
			close(fd);
		else if (fd == -1)
			return (free(filepath), EXIT_FAILURE);
	}
	else
		return (free(filepath), EXIT_FAILURE);
	free(filepath);
	return (EXIT_SUCCESS);
}
