/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bince < bince@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 23:07:53 by mel-yand          #+#    #+#             */
/*   Updated: 2024/09/26 15:49:15 by bince            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

// bince changed here

int	get_outfile(t_data *data)
{
	return (data->all_pipes->pipelines[data->index]->outfile_fd);
}

void	ft_echo(t_data *data, char **arg)
{
	int	i;
	int	n;

	i = 1;
	n = 0;
	if (arg[1] == NULL)
	{
		ft_putchar_fd('\n', get_outfile(data));
		return ;
	}
	while (arg[i] && ft_strncmp(arg[i], "-n", 2) == 0)
	{
		i++;
		n++;
	}
	while (arg[i])
	{
		ft_putstr_fd(arg[i], get_outfile(data));
		if (arg[i] && arg[i + 1])
			ft_putchar_fd(' ', get_outfile(data));
		i++;
	}
	if (n == 0)
		ft_putchar_fd('\n', get_outfile(data));
	data->status = 0;
}
