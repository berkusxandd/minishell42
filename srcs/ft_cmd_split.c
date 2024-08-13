/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bince < bince@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 06:47:34 by bince             #+#    #+#             */
/*   Updated: 2024/08/13 06:47:36 by bince            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*parse_pipes_in_quotes(char *str)
{
	int	i;
	int	q_type;

	q_type = 0;
	i = 0;
	while (str[i + 1])
	{
		q_type = quote_check(str[i], q_type);
		if (q_type != 0)
		{
			if (str[i] == '|')
				str[i] = -10;
		}
		i++;
	}
	return (str);
}

char	**deparse_pipes(char **parsed)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (parsed[i])
	{
		j = 0;
		while (parsed[i][j])
		{
			if (parsed[i][j] == -10)
				parsed[i][j] = '|';
			j++;
		}
		i++;
	}
	return (parsed);
}

char	*parse_space_in_quotes(char *str)
{
	int	i;
	int	q_type;

	q_type = 0;
	i = 0;
	while (str[i + 1])
	{
		q_type = quote_check(str[i], q_type);
		if (q_type != 0)
		{
			if (str[i] == ' ')
				str[i] = -4;
			else if (str[i] >= 9 && str[i] <= 13)
				str[i] = -3 * str[i];
		}
		i++;
	}
	return (str);
}

char	**deparse_spaces(char **parsed)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (parsed[i])
	{
		j = 0;
		while (parsed[i][j])
		{
			if (parsed[i][j] == -4)
				parsed[i][j] = ' ';
			else if (parsed[i][j] <= -27 && parsed[i][j] >= -39)
				parsed[i][j] = parsed[i][j] / -3;
			j++;
		}
		parsed[i] = quote_parser(parsed[i]);
		i++;
	}
	return (parsed);
}

char	**cmd_quote_parse(char *str)
{
	char	**parsed_cmds;

	str = parse_space_in_quotes(str);
	parsed_cmds = ft_split_str(str);
	if (!parsed_cmds)
		return (NULL);
	parsed_cmds = deparse_spaces(parsed_cmds);
	return (parsed_cmds);
}
