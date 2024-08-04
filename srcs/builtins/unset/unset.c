/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bince < bince@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 22:50:47 by mel-yand          #+#    #+#             */
/*   Updated: 2024/08/04 17:42:01 by bince            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	check_varname(t_data *data, char *varname, int *first)
{
	if (varname[0] == '_' && varname[1] == '\0')
		return (1);
	if (varname[0] != '_' && !ft_isalpha(varname[0]))
	{
		if (varname[0] == '-' && *first == 0)
		{
			ft_putstr_fd("Minishel: unset: ", 2);
			ft_putstr_fd(varname, 2);
			ft_putstr_fd(" invalid option\n", 2);
			data->status = 2;
			*first = -1;
		}
		return (1);
	}
	return (0);
}

void	del_var(t_data *data, char *varnam, int *first)
{
	int		valid;
	t_list	*var_env;

	valid = check_varname(data, varnam, first);
	var_env = find(data, varnam);
	if (var_env && valid == 0)
	{
		if (ft_strncmp(var_env->var, "PATH", 5) == 0)
			free_tab(data->path);
		if (var_env == data->env)
			data->env = var_env->next;
		ft_lstdelone(var_env, free);
	}
	data->status = 0;
}

void	ft_unset(t_data *data, char **arg)
{
	int	i;
	int	first;

	i = 1;
	first = 0;
	while (arg[i])
	{
		del_var(data, arg[i++], &first);
		if (first == -1)
			return ;
		first++;
	}
}
