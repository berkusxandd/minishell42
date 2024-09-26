/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bince < bince@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 17:48:57 by bince             #+#    #+#             */
/*   Updated: 2024/08/13 18:01:06 by bince            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_value(char *varname, t_list *env)
{
	while (env)
	{
		if (ft_strlen(varname) == ft_strlen(env->var))
		{
			if (ft_strncmp(env->var, varname, ft_strlen(varname)) == 0)
			{
				if (env->value)
					return (env->value);
				else
					return ("");
			}
		}
		env = env->next;
	}
	return ("");
}

char	*put_str_in_str(char *dest, char *source, int start_index,
		int end_index)
{
	char	*parsed_str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	parsed_str = malloc(sizeof(char) * (ft_strlen(dest) + ft_strlen(source)
				+ 1));
	if (!parsed_str)
		return (NULL);
	while (dest[i])
	{
		if (i == start_index)
		{
			while (source[j - start_index])
			{
				parsed_str[j] = source[j - start_index];
				j++;
			}
		}
		else if (i > end_index || i < start_index)
			parsed_str[j++] = dest[i];
		i++;
	}
	return (put_str_in_str_utils(dest, parsed_str, j), parsed_str);
}

char	*find_val_put_str(char *parsed_str, int i, int j, t_data core)
{
	char	*var_name;
	char	*var_value;

	var_name = cut_str(parsed_str, i, j, 1);
	if (!var_name)
		return (NULL);
	if (var_name[0] == '?')
	{
		var_value = ft_itoa(core.status);
		free(var_name);
		if (!var_value)
			return (NULL);
		parsed_str = put_str_in_str(parsed_str, var_value, j - 1, j);
		return (free(var_value), parsed_str);
	}
	else if (ft_isdigit(var_name[0]))
		return (var_digit(var_name, parsed_str, j));
	else
	{
		var_value = get_value(var_name, core.env);
		parsed_str = put_str_in_str(parsed_str, var_value, j - 1, i - 1);
		return (free(var_name), parsed_str);
	}
}

char	*create_parsed_str(int *i, int j, char *parsed_str, t_data core)
{
	char	*tmp_var_name;
	char	*tmp_parsed;

	if (*i == j)
		parsed_str[j - 1] = '$';
	else
	{
		tmp_var_name = cut_str(parsed_str, *i, j, 1);
		if (!tmp_var_name)
			return (NULL);
		tmp_parsed = parsed_str;
		parsed_str = find_val_put_str(parsed_str, *i, j, core);
		if (!parsed_str)
		{
			free(tmp_var_name);
			free(tmp_parsed);
			return (NULL);
		}
		*i = j - 1 + ft_strlen(get_value(tmp_var_name, core.env));
		free(tmp_var_name);
	}
	return (parsed_str);
}

char	*parse_input_args(char *input, t_data core)
{
	int		i;
	int		j;
	char	*parsed_str;

	parsed_str = ft_strdup(input);
	free(input);
	if (!parsed_str)
		return (NULL);
	i = 0;
	while (parsed_str[i])
	{
		if (parsed_str[i] == -3)
		{
			i++;
			j = i;
			while (parsed_str[i] && (arg_conditions(parsed_str[i])))
				i++;
			parsed_str = create_parsed_str(&i, j, parsed_str, core);
			if (!parsed_str)
				return (NULL);
		}
		else
			i++;
	}
	return (parsed_str);
}
