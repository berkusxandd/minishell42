/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-yand <mel-yand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 17:14:15 by mel-yand          #+#    #+#             */
/*   Updated: 2024/08/02 23:55:59 by mel-yand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

//--------------------------------------------------//
//					BUILTIN_EXEC					//
//--------------------------------------------------//

int	is_builtin(char *cmd);
int	exec_builtins(t_data *data, t_pipeline *node);

//--------------------------------------------------//
//					FILE_HANDLER					//
//--------------------------------------------------//

void	open_file(t_data *data);

//--------------------------------------------------//
//					INIT_EXEC						//
//--------------------------------------------------//

void	execution(t_data *data);

//--------------------------------------------------//
//					UTILS_EXEC						//
//--------------------------------------------------//

int		count_cmd(t_data *data);
void	creat_env_char(t_data *data);
char	*get_cmd_path_2(char **arg);
char	*get_cmd_path(t_data *data, char **arg);

//--------------------------------------------------//
//					UTILS_PIPELINE					//
//--------------------------------------------------//

void	reset_fd(int *fd_ptr);
void	close_pipe(int pipe[2]);
void	close_all_pipe(t_all_pipelines *all_pipes);
void	creat_pipe(t_pipeline **node);
void	std_handler(t_pipeline **node, int nb_process);

#endif