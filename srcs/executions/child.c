/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bince < bince@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 12:41:11 by bince             #+#    #+#             */
/*   Updated: 2024/08/13 13:16:48 by bince            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	wait_child(t_data *data, pid_t exit_status, int nb_process)
{
	int		status;
	pid_t	child_pid;
	int		i;
	int		term_sig;

	i = 0;
	while (i < nb_process)
	{
		child_pid = waitpid(data->all_pipes->pipelines[i]->pid, &status, 0);
		if (child_pid == exit_status)
		{
			if (WIFEXITED(status))
				data->status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
			{
				term_sig = WTERMSIG(status);
				if (term_sig == SIGINT)
					data->status = 128 + SIGINT;
				else
					data->status = 128 + term_sig;
			}
		}
		i++;
	}
}

void	child(t_data *d)
{
	if (d->all_pipes->pipelines[d->index]->infile_fd == -1)
		free_exit(d, EXIT_FAILURE);
	else
	{
		if (dup2(d->all_pipes->pipelines[d->index]->infile_fd, READ) == -1)
			return (perror("Minishell: Error"));
	}
	if (d->all_pipes->pipelines[d->index]->outfile_fd == -1)
		free_exit(d, EXIT_FAILURE);
	else
	{
		if (dup2(d->all_pipes->pipelines[d->index]->outfile_fd, WRITE) == -1)
			return (perror("Minishell: Error"));
	}
	close_all_pipe(d->all_pipes);
	if (exec_builtins(d, d->all_pipes->pipelines[d->index]) == 1)
	{
		free_exit(d, 127);
		return ;
	}
	exec_cmd(d, d->all_pipes->pipelines[d->index]->cmd);
}
