/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bince < bince@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 20:50:08 by mel-yand          #+#    #+#             */
/*   Updated: 2024/08/13 11:51:58 by bince            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_builtin(char *cmd)
{
	if (cmd == NULL)
		return (0);
	else if (!ft_strncmp(cmd, "cd", 3)
			|| !ft_strncmp(cmd, "echo", 5)
			|| !ft_strncmp(cmd, "env", 4)
			|| !ft_strncmp(cmd, "export", 7)
			|| !ft_strncmp(cmd, "pwd", 4)
			|| !ft_strncmp(cmd, "unset", 6)
			|| !ft_strncmp(cmd, "exit", 5))
		return (1);
	return (0);
}

int	exec_builtins(t_data *data, t_pipeline *node)
{
	if (is_builtin(node->cmd[0]) == 0)
		return (0);
	if (ft_strncmp(node->cmd[0], "cd", 3) == 0)
		ft_cd(data, node->cmd);
	else if (ft_strncmp(node->cmd[0], "echo", 5) == 0)
		ft_echo(data, node->cmd);
	else if (ft_strncmp(node->cmd[0], "env", 4) == 0)
		ft_env(data, data->env, node->cmd);
	else if (ft_strncmp(node->cmd[0], "export", 7) == 0)
		ft_export(data, node->cmd);
	else if (ft_strncmp(node->cmd[0], "pwd", 4) == 0)
		ft_pwd(data);
	else if (ft_strncmp(node->cmd[0], "unset", 6) == 0)
		ft_unset(data, node->cmd);
	else if (ft_strncmp(node->cmd[0], "exit", 5) == 0)
		ft_exit(data, node->cmd);
	return (1);
}
