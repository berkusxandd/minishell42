/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bince < bince@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 20:21:46 by mel-yand          #+#    #+#             */
/*   Updated: 2024/09/27 11:57:14 by bince            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

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

void	print_variable(t_list *node)
{
	ft_putstr_fd("declare -x ", 1);
	ft_putstr_fd(node->var, 1);
	if (node->value)
	{
		ft_putstr_fd("=\"", 1);
		ft_putstr_fd(node->value, 1);
		ft_putstr_fd("\"", 1);
	}
	ft_putstr_fd("\n", 1);
}

int	compare_vars(t_list *a, t_list *b)
{
	int	i;

	i = 0;
	while (a->var[i] && b->var[i] && a->var[i] == b->var[i])
		i++;
	return (a->var[i] - b->var[i]);
}

t_list	*find_min(t_list *env, t_list *last_min)
{
	t_list	*min;
	t_list	*current;

	min = NULL;
	current = env;
	while (current)
	{
		if ((!min || compare_vars(current, min) < 0) && (!last_min
				|| compare_vars(current, last_min) > 0))
			min = current;
		current = current->next;
	}
	return (min);
}

void	export_no_args(t_list *env)
{
	t_list	*min;
	t_list	*current;

	if (!env)
		return ;
	current = NULL;
	min = find_min(env, current);
	while (min)
	{
		print_variable(min);
		current = min;
		min = find_min(env, current);
	}
}
