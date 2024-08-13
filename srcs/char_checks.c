/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_checks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bince < bince@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 06:44:27 by bince             #+#    #+#             */
/*   Updated: 2024/08/13 07:00:39 by bince            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_token(char c)
{
	if (c == '>' || c == '<' || c == -1 || c == -2)
		return (1);
	else
		return (0);
}
int	is_set(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	else
		return (0);
}

int	is_cur_token(char c, char token)
{
	if (token == '>' || token == -2)
	{
		if (c == '>' || c == -2)
			return (1);
		else
			return (0);
	}
	else
		return (c == token);
}
int	arg_conditions(char c)
{
	if (ft_isalnum(c) || c == '_' || c == '?')
		return (1);
	else
		return (0);
}
