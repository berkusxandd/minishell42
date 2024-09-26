/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bince < bince@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 12:45:21 by bince             #+#    #+#             */
/*   Updated: 2024/08/13 19:36:17 by bince            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_str(char **str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	count_list(t_list *lst)
{
	int		i;
	t_list	*tmp;

	i = 0;
	tmp = lst;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

t_list	*find(t_data *data, char *varname)
{
	t_list	*tmp;

	tmp = data->env;
	while (tmp)
	{
		if (ft_strncmp(tmp->var, varname, ft_strlen(varname) + 1) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

char	*put_str_in_str_utils(char *dest, char *parsed_str, int j)
{
	free(dest);
	parsed_str[j] = '\0';
	return (parsed_str);
}

char	*var_digit(char *var_name, char *parsed_str, int j)
{
	char	*var_value;

	var_value = "";
	free(var_name);
	parsed_str = put_str_in_str(parsed_str, var_value, j - 1, j);
	return (parsed_str);
}
