/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bince < bince@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 02:23:28 by mel-yand          #+#    #+#             */
/*   Updated: 2024/08/13 19:45:35 by bince            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_pathfile(char *filename)
{
	char	*pwd;
	char	*filepath;
	char	*tmp;

	if (filename == NULL)
		return (NULL);
	if (filename[0] == '/')
		return (ft_strdup(filename));
	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
		return (NULL);
	tmp = ft_strjoin("/", filename);
	if (tmp == NULL)
		return (free(pwd), NULL);
	filepath = ft_strjoin(pwd, tmp);
	if (filepath == NULL)
	{
		free(pwd);
		free(tmp);
		return (NULL);
	}
	free(pwd);
	free(tmp);
	return (filepath);
}

int	file_error(t_pipeline *node, char *filepath, int err)
{
	if (err == 1)
	{
		perror("Minishell: Error INF");
		node->infile_fd = -1;
	}
	else if (err == 2)
	{
		perror("Minishell: Error OUTF");
		node->outfile_fd = -1;
	}
	return (-1);
}

int	open_infile(t_pipeline *node)
{
	int		i;
	int		fd;
	char	*filepath;

	i = 0;
	while (node->infiles[i])
	{
		filepath = filepath_init(filepath, &fd, i, node);
		if (filepath == NULL)
			return (-1);
		if (access(filepath, R_OK) == 0)
		{
			fd = open(filepath, O_RDONLY);
			if (node->infiles[i + 1] == NULL && fd != -1)
				node->infile_fd = fd;
			else if (fd != -1)
				close(fd);
			else if (fd == -1)
				return (free(filepath), file_error(node, filepath, 1));
		}
		else
			return (free(filepath), file_error(node, filepath, 1));
		i = free_fp_inc_i(i, filepath);
	}
	return (0);
}

int	open_outfile(t_pipeline *node)
{
	int		i;
	int		fd;
	char	*filepath;

	i = 0;
	while (node->outfiles[i])
	{
		if (node->outfiles[i][0] == '0')
		{
			if (open_outfile_0(node, filepath, fd, i) == -1)
				return (file_error(node, filepath, 2));
		}
		else if (node->outfiles[i][0] == 'x')
		{
			if (open_outfile_x(node, filepath, fd, i) == -1)
				return (file_error(node, filepath, 2));
		}
		i++;
	}
	return (0);
}

int	open_file(t_data *data)
{
	int	i;

	i = 0;
	while (data->all_pipes->pipelines[i])
	{
		if (data->all_pipes->pipelines[i]->here_docs[0] != NULL)
		{
			if (heredocs(data->all_pipes->pipelines[i]) == -1)
				return (-1);
		}
		if (data->all_pipes->pipelines[i]->infiles[0] != NULL)
		{
			if (open_infile(data->all_pipes->pipelines[i]) == -1)
				return (-1);
		}
		if (data->all_pipes->pipelines[i]->outfiles[0] != NULL)
		{
			if (open_outfile(data->all_pipes->pipelines[i]) == -1)
				return (-1);
		}
		i++;
	}
	return (0);
}
