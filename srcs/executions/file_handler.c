/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bince < bince@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 02:23:28 by mel-yand          #+#    #+#             */
/*   Updated: 2024/08/08 18:15:06 by bince            ###   ########.fr       */
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
		return (NULL);
	filepath = ft_strjoin(pwd, tmp);
	if (filepath == NULL)
		return (NULL);
	free(pwd);
	free(tmp);
	return (filepath);
}

void	open_infile(t_pipeline *node)
{
	int		i;
	int		fd;
	char	*filepath;

	i = 0;
	while (node->infiles[i])
	{
		filepath = NULL;
		fd = -1;
		filepath = get_pathfile(node->infiles[i]);
		printf("path_in %s\n", filepath);
		printf("fd_in init = %d\n", fd);
		if (access(filepath, R_OK) == 0)
		{
			fd = open(filepath, O_RDONLY);
			printf("fd0_in = %d\n", fd);
			if (node->infiles[i + 1] == NULL && fd != -1)
				node->infile_fd = fd;
			else
				close(fd);
		}
		else
			perror("Minishell: Error INF");
		free(filepath);
		i++;
	}
}
// i changed here
void	open_outfile(t_pipeline *node)
{
	int		i;
	int		fd;
	char	*filepath;

	i = 0;
	while (node->outfiles[i])
	{
		if (node->outfiles[i][0] == '0')
		{
		node->outfiles[i]++;
		filepath = NULL;
		fd = -1;
		filepath = get_pathfile(node->outfiles[i]);
		printf("path_out %s\n", filepath);
		printf("fd_out init = %d\n", fd);
		if (access(filepath, W_OK) == 0 || access(filepath, F_OK) == -1)
		{
			fd = open(filepath, O_WRONLY | O_CREAT | O_TRUNC, 0666);
			printf("fd0_out = %d\n", fd);
			if (node->outfiles[i + 1] == NULL && fd != -1)
				node->outfile_fd = fd;
			else
				close(fd);
		}
		else
			perror("Minishell: Error OUTF");
		free(filepath);
		}
		else if (node->outfiles[i][0] == 'x')
		{
			node->outfiles[i]++;
			filepath = NULL;
			fd = -1;
			filepath = get_pathfile(node->outfiles[i]);
			printf("path_out %s\n", filepath);
			printf("fd_out init = %d\n", fd);
			if (access(filepath, W_OK) == 0 || access(filepath, F_OK) == -1)
			{
				fd = open(filepath,  O_WRONLY | O_CREAT | O_APPEND, 0666);
				printf("fd0_out = %d\n", fd);
				if (node->outfiles[i + 1] == NULL && fd != -1)
					node->outfile_fd = fd;
				else
					close(fd);
			}
			else
				perror("Minishell: Error OUTF");
			free(filepath);
		}

		i++;
	}
}


void	open_file(t_data *data)
{
	int	i;

	i = 0;
	while (data->all_pipes->pipelines[i])
	{
		if (data->all_pipes->pipelines[i]->here_docs[0] != NULL)
			heredocs(data->all_pipes->pipelines[i]);
		if (data->all_pipes->pipelines[i]->infiles[0] != NULL)
		{
			open_infile(data->all_pipes->pipelines[i]);
			printf("fd1_in = %d\n", data->all_pipes->pipelines[i]->infile_fd);
		}
		if (data->all_pipes->pipelines[i]->outfiles[0] != NULL)
		{
			open_outfile(data->all_pipes->pipelines[i]);
			printf("fd1_out = %d\n", data->all_pipes->pipelines[i]->outfile_fd);
		}
		i++;
	}
}
