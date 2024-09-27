/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bince < bince@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 11:53:40 by bince             #+#    #+#             */
/*   Updated: 2024/09/27 11:53:42 by bince            ###   ########.fr       */
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
