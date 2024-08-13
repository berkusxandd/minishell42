/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bince < bince@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 18:50:30 by mel-yand          #+#    #+#             */
/*   Updated: 2024/08/13 12:35:46 by bince            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	print_cd_error(char *path)
{
	ft_putstr_fd("Minishell: cd: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putchar_fd('\n', 2);
}

void	update_pwd(t_data *data, char *path)
{
	t_list	*env;
	char	*newpwd;

	if (data->status == 0)
	{
		env = find(data, "PWD");
		if (env == NULL)
			return ;
		newpwd = getcwd(NULL, 0);
		if (newpwd == NULL)
			return (ft_putstr_fd("Error with getcwd\n", 2));
		free(env->value);
		env->value = ft_strdup(newpwd);
		free(newpwd);
	}
	else
		print_cd_error(path);
}

void	update_oldpwd(t_data *data)
{
	t_list	*old;
	t_list	*pwd;

	old = find(data, "OLDPWD");
	pwd = find(data, "PWD");
	if (old && pwd)
	{
		free(old->value);
		old->value = ft_strdup(pwd->value);
	}
	else if (!pwd)
	{
		free(old->value);
		old->value = getcwd(NULL, 0);
	}
}

void	cd_home(t_data *data, char *path)
{
	t_list	*env;

	env = find(data, "HOME");
	if (env)
	{
		data->status = chdir(env->value) * -1;
		update_oldpwd(data);
		update_pwd(data, path);
	}
	else
	{
		ft_putstr_fd("Minishell: cd: HOME not set\n", 2);
		data->status = 1;
	}
}

void	ft_cd(t_data *data, char **arg)
{
	char	*path;
	char	pwd[4096];

	if (count_str(arg) > 2)
	{
		ft_putstr_fd("Minishell: cd: too many arguments\n", 2);
		data->status = 1;
		return ;
	}
	path = arg[1];
	if (path == NULL)
		cd_home(data, path);
	else
	{
		data->status = chdir(path) * -1;
		if ((data->status == 1) || (getcwd(pwd, 4096) == NULL))
		{
			print_cd_error(path);
			data->status = 1;
			return ;
		}
		update_oldpwd(data);
		update_pwd(data, path);
	}
}
