/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bince < bince@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 17:45:22 by mel-yand          #+#    #+#             */
/*   Updated: 2024/08/13 11:43:21 by bince            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	modif_var(t_data *data, char **arg, int empty)
{
	t_list *env;

	env = find(data, arg[0]);
	free(env->value);
	if (arg[1])
		env->value = ft_strdup(arg[1]);
	else if (empty == 0)
		env->value = ft_strdup("");
	else
		env->value = NULL;
}

int	is_new_var(t_data *data, char *varname)
{
	t_list *env;

	env = find(data, varname);
	if (env == NULL)
		return (1);
	else
		return (0);
}

void	set_datapath(t_data *data, char **tmp)
{
	if (data->path == NULL)
		data->path = ft_split(tmp[1], ':');
	else
	{
		free_tab(data->path);
		data->path = ft_split(tmp[1], ':');
	}
}

void	export_var(t_data *data, char *arg)
{
	char	**tmp;
	char	*equal;
	int		empty;

	empty = 0;
	equal = ft_strchr(arg, 61);
	if (equal == NULL)
		empty = 1;
	tmp = ft_split(arg, '=');
	if (tmp == NULL)
		return ;
	if (is_new_var(data, tmp[0]))
	{
		if (empty == 0 && tmp[1] == NULL)
			ft_lstadd_back(&data->env, ft_lstnew(tmp[0], ""));
		else
			ft_lstadd_back(&data->env, ft_lstnew(tmp[0], tmp[1]));
	}
	else
		modif_var(data, tmp, empty);
	if (ft_strncmp(tmp[0], "PATH", 5) == 0)
		set_datapath(data, tmp);
	free_tab(tmp);
}

void	ft_export(t_data *data, char **arg)
{
	int	i;

	i = 1;
	data->status = 0;
	if (arg[i])
	{
		while (arg[i])
		{
			if (valid_name(data, arg[i]))
				export_var(data, arg[i]);
			i++;
		}
	}
	else
		ft_putstr_fd("\n", 1);
}
