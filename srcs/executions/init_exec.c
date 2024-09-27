/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bince < bince@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 19:08:42 by mel-yand          #+#    #+#             */
/*   Updated: 2024/09/27 11:52:15 by bince            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

pid_t	start_exec(t_data *data)
{
	pid_t	pid;

	if (count_cmd(data) == 1
		&& is_builtin(data->all_pipes->pipelines[0]->cmd[0]) == 1)
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
		if (tmp[i]->cmd[0] == NULL)
			tmp[i]->pid = 0;
		else
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
	if (open_file(data) == -1)
	{
		close_all_pipe(data->all_pipes);
		close_here_doc(data->all_pipes);
		data->status = 1;
		return (free_tab(data->env_array));
	}
	if (g_signals.here_doc_quit == 1)
	{
		free_tab(data->env_array);
		return ;
	}
	std_handler(data->all_pipes->pipelines, nb_process);
	exit_status = launch_cmd(data, nb_process);
	close_all_pipe(data->all_pipes);
	if (exit_status != -1)
		wait_child(data, exit_status, nb_process);
	close_here_doc(data->all_pipes);
	free_tab(data->env_array);
}
