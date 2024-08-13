/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bince < bince@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 13:19:12 by mel-yand          #+#    #+#             */
/*   Updated: 2024/08/13 12:24:47 by bince            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	ft_pwd(t_data *data, char **arg)
{
	char	*pwd;

	data->status = 0;
	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		perror("pwd: error retrieving current directory: getcwd");
		data->status = 1;
		return ;
	}
	if (arg[1] != NULL)
	{
		ft_putstr_fd("minipwd doesn't take arguments\n", 2);
		data->status = 2;
		free(pwd);
		return ;
	}
	ft_putstr_fd(pwd, 1);
	ft_putchar_fd('\n', 1);
	free(pwd);
}
