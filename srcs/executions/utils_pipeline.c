/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bince < bince@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 20:15:46 by mel-yand          #+#    #+#             */
/*   Updated: 2024/08/08 19:00:58 by bince            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	reset_fd(int *fd_ptr)
{
	close(*fd_ptr);
	*fd_ptr = -1;
}

void	close_pipe(int pipe[2])
{
	if (pipe[READ] != -1)
		reset_fd(&pipe[READ]);
	if (pipe[WRITE] != -1)
		reset_fd(&pipe[WRITE]);
}

void	close_all_pipe(t_all_pipelines *all_pipes)
{
	int	i;

	i = 0;
	while (all_pipes->pipelines[i])
	{
		close_pipe(all_pipes->pipelines[i]->pipefd);
		if (all_pipes->pipelines[i]->infile_fd != -1 && all_pipes->pipelines[i]->infile_fd != 0)
			reset_fd(&all_pipes->pipelines[i]->infile_fd);
		if (all_pipes->pipelines[i]->outfile_fd != -1 && all_pipes->pipelines[i]->outfile_fd != 1)
			reset_fd(&all_pipes->pipelines[i]->outfile_fd);
		i++;
	}
}

void	creat_pipe(t_pipeline **node)
{
	int	i;

	i = 0;
	while (node[i])
	{
		if (node[i]->outfiles[0] == NULL && node[i + 1])
		{
			if (pipe(node[i]->pipefd) == -1)
			{
				ft_putstr_fd(node[i]->cmd[0], 2);
				ft_putstr_fd(": Error with pipe creation\n", 2); /*maybe modif*/
			}
			printf("pipe creer index %d\n", i);
			printf("pipe0=%d, pipe1=%d\n", node[i]->pipefd[0], node[i]->pipefd[1]);
		}
		else
		{
			node[i]->pipefd[0] = -1;
			node[i]->pipefd[1] = -1;
		}
		i++;
	}
}

void	std_handler(t_pipeline **node, int nb_process)
{
	int	i;

	i = 0;
	// if (node[i] && (node[i]->pipefd[0] != -1 && node[i]->pipefd[1] != -1))
	// 	node[i]->outfile_fd = node[i]->pipefd[WRITE];
	// i++;
	while (node[i])
	{
		if (i != 0 && node[i - 1]->pipefd[0] != -1)
			node[i]->infile_fd = node[i - 1]->pipefd[READ];
		if(i != nb_process - 1)
		{
			if (node[i]->pipefd[0] != -1 && node[i]->pipefd[1] != -1)
				node[i]->outfile_fd = node[i]->pipefd[WRITE];
		}
		i++;
	}
}
