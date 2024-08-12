/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-yand <mel-yand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 22:42:43 by mel-yand          #+#    #+#             */
/*   Updated: 2024/08/12 22:45:00 by mel-yand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	only_digit(char *arg)
{
	int	i;
	
	i = 0;
	if (arg[0] == '-' || arg[0] == '+')
		i++;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	ll_max(char *s)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (s[i] == '-' || s[i] == '+')
		i++;
	while (ft_isdigit(s[i]) == 1)
	{
		i++;
		j++;
	}
	if (j > 19)
		return (1);
	return (0);
}

int	check_limits(unsigned long long n, int signe)
{
	if (signe == -1 && n > 9223372036854775808uLL)
		return (1);
	if (signe == 1 && n > 9223372036854775807uLL)
		return (1);
	return (0);
}

int	is_too_big(char *cmd)
{
	int					i;
	int					signe;
	unsigned long long	n;

	i = 0;
	signe = 1;
	n = 0;
	if (ll_max(cmd) == 1)
		return (1);
	if (cmd[i] == '-' || cmd[i] == '+')
	{
		if (cmd[i] == '-')
			signe = -1;
		i++;
	}
	while (ft_isdigit(cmd[i]) == 1)
	{
		n = 10 * n + cmd[i] - '0';
		i++;
	}
	if (check_limits(n, signe) == 1)
		return (1);
	return (0);
}

long long	ft_atoll(const char *str)
{
	int			i;
	int			n;
	long long	value;

	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	n = 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			n = n * (-1);
		i++;
	}
	value = 0;
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		value = value * 10 + (str[i] - 48);
		if ((value * n) > INT_MAX || (value * n) < INT_MIN)
			return (LLONG_MAX);
		i++;
	}
	return (value * n);
}
