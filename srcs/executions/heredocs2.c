/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-yand <mel-yand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 13:14:36 by bince             #+#    #+#             */
/*   Updated: 2024/08/13 17:20:23 by mel-yand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	open_err_hd(char *filename)
{
	perror("Error open");
	free(filename);
	return (-1);
}

void	heredocs_2(t_pipeline *pipeline, int *i, int fd, char *filename)
{
	int	tmp_i;

	tmp_i = *i;
	if (pipeline->here_docs[tmp_i + 1] != NULL)
	{
		close(fd);
		unlink(filename);
		free(filename);
	}
	else
	{
		pipeline->infile_fd = fd;
		pipeline->here_filename = filename;
	}
	*i = tmp_i + 1;
}
