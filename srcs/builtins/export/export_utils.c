/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bince < bince@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 20:21:46 by mel-yand          #+#    #+#             */
/*   Updated: 2024/08/04 17:41:50 by bince            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	print_error_export(t_data *data, char *varname)
{
	if (varname[0] == '-')
	{
		ft_putstr_fd("Minishell: export: -", 2);
		ft_putchar_fd(varname[1], 2);
		ft_putstr_fd(": invalid option\n", 2);
		data->status = 2;
	}
	else
	{
		ft_putstr_fd("Minishell: export: ", 2);
		ft_putstr_fd(varname, 2);
		ft_putstr_fd(": not a valid identifier\n", 2);
		data->status = 1;
	}
	return (0);
}

int	valid_name(t_data *data, char *arg)
{
	int	i;

	if (arg[0] == '_' && (arg[1] == '\0' || arg[1] == '='))
		return (0);
	if (arg[0] != '_' && !ft_isalpha(arg[0]))
		return (print_error_export(data, arg));
	i = 1;
	while (arg[i] && arg[i] != '=')
	{
		if (arg[i] != '_' && !ft_isalnum(arg[i]))
			return (print_error_export(data, arg));
		i++;
	}
	return (1);
}
