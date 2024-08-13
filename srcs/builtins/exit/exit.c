/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bince < bince@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 18:34:46 by mel-yand          #+#    #+#             */
/*   Updated: 2024/08/13 11:57:48 by bince            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

// void	exit_handler(t_data *core)
// {
// 	int	exit_status;

// 	exit_status = core->status;
// 	free_env(&core->env);
// 	free_tab(core->path);
// 	clear_history();
// 	exit(exit_status);
// }

void	free_exit(t_data *data, int err)
{
	free_tab(data->path);
	free_env(&(data->env));
	free_tab(data->env_array);
	free_all_pipelines(data->all_pipes);
	clear_history();
	exit(err);
}

void	check_arg(t_data *data, char **arg)
{
	if (only_digit(arg[1]) == EXIT_FAILURE || is_too_big(arg[1]) == EXIT_FAILURE)
	{
		ft_putstr_fd("Minishell: exit:", 2);
		ft_putstr_fd(arg[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		free_exit(data, 2);
	}
}

void	ft_exit(t_data *data, char **arg)
{
	int				nb_arg;
	long long int	err;

	nb_arg = count_str(arg);
	if (nb_arg == 1)
		free_exit(data, EXIT_SUCCESS);
	else
	{
		check_arg(data, arg);
		if (nb_arg > 2)
		{
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			data->status = 1;
		}
		else
		{
			err = ft_atoi(arg[1]);
			if (err < 0)
				data->status = 256 - ((err * -1) % 256);
			else
				data->status = err % 256;
			ft_putstr_fd("exit\n", 2);
			free_exit(data,data->status);
		}
	}
}
