/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bince < bince@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 13:19:12 by mel-yand          #+#    #+#             */
/*   Updated: 2024/08/04 17:41:57 by bince            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	ft_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		// ft_putstr_fd("pwd: error retrieving current directory:  getcwd: ", 2);
		// ft_putstr_fd("cannot access parent directories: No such file or ", 2);
		// ft_putstr_fd("directory\n", 2);
		perror("pwd: error retrieving current directory: getcwd");
		/*CHANGE STATUS ERROR TO 1*/
		return ;
	}
	ft_putstr_fd(pwd, 1);
	ft_putchar_fd('\n', 1);
	free(pwd);
}
