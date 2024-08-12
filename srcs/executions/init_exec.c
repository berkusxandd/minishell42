/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bince < bince@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 19:08:42 by mel-yand          #+#    #+#             */
/*   Updated: 2024/08/13 00:27:49 by bince            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
void	wait_child(t_data *data, pid_t exit_status, int nb_process)
{
	int		status;
	pid_t	child_pid;
	int		i;
	int term_sig;

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

// void    free_exit(t_data *data, int err)
// {
//     free_tab(data->path);
//    	free_env(&(data->env));
//     free_tab(data->env_array);
//     free_all_pipelines(data->all_pipes);
//     exit(err);
// }

void	exec_cmd(t_data *data, char **arg)
{
	char	*cmd;

	cmd = get_cmd_path(data, arg);
	if (cmd != NULL && access(cmd, X_OK) == 0)
		execve(cmd, arg, data->env_array);
	if (cmd != NULL && access(cmd, F_OK) == 0)
	{
		ft_putstr_fd("MiniShell: ", 2);
		ft_putstr_fd(arg[0], 2);
		ft_putstr_fd(": Permission denied\n", 2);
		free(cmd);
		free_exit(data, 126);
	}
	ft_putstr_fd("MiniShell: ", 2);
	ft_putstr_fd(arg[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	free_exit(data, 127);
}

void	child(t_data *data)
{
	if (dup2(data->all_pipes->pipelines[data->index]->infile_fd, READ) == -1)
		return (perror("Minishell: Error"));
	if (dup2(data->all_pipes->pipelines[data->index]->outfile_fd, WRITE) == -1)
		return (perror("Minishell: Error"));
	close_all_pipe(data->all_pipes);
	if (exec_builtins(data, data->all_pipes->pipelines[data->index]) == 1)
	{
		free_exit(data,127);
		return ;
	}
	exec_cmd(data, data->all_pipes->pipelines[data->index]->cmd);
}

pid_t	start_exec(t_data *data)
{
	pid_t	pid;

	if (count_cmd(data) == 1 && is_builtin(data->all_pipes->pipelines[0]->cmd[0]) == 1)
	{
		exec_builtins(data, data->all_pipes->pipelines[0]);
		return (-1);
	}
	pid = fork();
	if (pid < 0)
	{
		perror("MiniShell: Error");
		return (-1);
	}
	else if (pid == 0)
	{
		child(data);
	}
	return (pid);
}

int	launch_cmd(t_data *data, int nb_process)
{
	t_pipeline	**tmp;
	pid_t		exit_status;
	int			i;

	tmp = data->all_pipes->pipelines;
	exit_status = 0;
	i = 0;
	while (tmp[i] && exit_status != -1 && i < nb_process)
	{
		data->index = i;
		tmp[i]->pid = start_exec(data);
		exit_status = tmp[i]->pid;
		i++;
	}
	return (exit_status);
}

void	close_here_doc(t_all_pipelines *all_pipes)
{
	int	i;

	i = 0;
	while (all_pipes->pipelines[i])
	{
		if (all_pipes->pipelines[i]->here_filename != NULL)
			unlink(all_pipes->pipelines[i]->here_filename);
		i++;
	}
}

void	execution(t_data *data)
{
	int	nb_process;
	int	exit_status;

	nb_process = count_cmd(data);
	creat_env_char(data);
	creat_pipe(data->all_pipes->pipelines);
	open_file(data);
	std_handler(data->all_pipes->pipelines, nb_process);
	exit_status = launch_cmd(data, nb_process);
	close_all_pipe(data->all_pipes);
	if (exit_status != -1)
		wait_child(data, exit_status, nb_process);
	close_here_doc(data->all_pipes);
	free_tab(data->env_array);
}
