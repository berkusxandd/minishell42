/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bince < bince@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 23:07:53 by mel-yand          #+#    #+#             */
/*   Updated: 2024/09/27 11:54:50 by bince            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	get_outfile(t_data *data)
{
	return (data->all_pipes->pipelines[data->index]->outfile_fd);
}

void	check_echo_arg(char **arg, int *i, int *n)
{
	int	j;

	while (arg[*i])
	{
		j = 0;
		if (arg[*i][j] == '-' && arg[*i][j + 1] == 'n')
		{
			j += 2;
			while (arg[*i][j] && (arg[*i][j] == 'n' || arg[*i][j] == 'e'))
				j++;
			if (arg[*i][j] == '\0')
			{
				(*n) = 1;
				(*i)++;
			}
			else
				break ;
		}
		else
			break ;
	}
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
	check_echo_arg(arg, &i, &n);
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
