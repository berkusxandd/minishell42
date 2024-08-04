/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_fonction.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bince < bince@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 17:04:10 by mel-yand          #+#    #+#             */
/*   Updated: 2024/08/04 17:42:20 by bince            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void free_tab(char **tab)
{
    int i = 0;

	if (tab)
	{
		while (tab[i])
		{
			free(tab[i]);
			i++;
		}
		free(tab);
    }
}

void	free_env(t_list **env)
{
	t_list *cur;
	t_list *prev;

	cur = *env;
	while (cur)
	{
		prev = cur;
		cur = cur->next;
		free(prev->var);
		free(prev->value);
		free(prev);
	}
}

void	free_all(t_data *data)
{
	free_tab(data->path);
	free_env(&data->env);
}

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
