/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bince < bince@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 20:23:24 by mel-yand          #+#    #+#             */
/*   Updated: 2024/08/06 13:48:47 by bince            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_cmd(t_data *data)
{
	int				i;
	t_all_pipelines	*tmp;

	i = 0;
	if (data == NULL || data->all_pipes == NULL)
		return (0);
	tmp = data->all_pipes;
	while (tmp->pipelines[i])
		i++;
	// printf("nb cmd %d\n", i);
	return (i);
}

void	creat_env_char(t_data *data)
{
	int		i;
	t_list	*tmp_env;
	char	**env_array;
	char	*var_tmp;

	i = count_list(data->env);
	env_array = malloc(sizeof(char *) * (i + 1));
	if (env_array == NULL)
		return ;/*quitter minishell ?*/
	tmp_env = data->env;
	i = 0;
	while (tmp_env)
	{
		if (tmp_env->value != NULL)
		{
			var_tmp = ft_strjoin("=",tmp_env->value);
			env_array[i] = ft_strjoin(tmp_env->var, var_tmp);
			free(var_tmp);
			i++;
		}
		tmp_env = tmp_env->next;
	}
	env_array[i] = NULL;
	data->env_array = env_array;
}

char	*get_cmd_path_2(char **arg)
{
	char	*pwd;
	char	*tmp;
	char	*tmp_path;

	tmp_path = NULL;
	if (arg[0] == NULL)
		return (NULL);
	else if (arg[0][0] == '/')
		return (ft_strdup(arg[0]));
	else if (arg[0][0] == '.')
	{
		pwd = getcwd(NULL, 0);
		tmp = ft_strjoin("/", arg[0]);
		tmp_path = ft_strjoin(pwd, tmp);
		free(pwd);
		free(tmp);
	}
	return (tmp_path);
}

char	*get_cmd_path(t_data *data, char **arg)
{
	int		i;
	char	*cmd;
	char	*tmp_path;

	i = 0;

	// i added this part ---------
	if (!data->path)
		return NULL;
	//------------------------
	if (arg == NULL || arg[0][0] == '/' || arg[0][0] == '.')
		return (get_cmd_path_2(arg));
	cmd = arg[0];
	if (access(cmd, F_OK | X_OK) == 0)
		return (cmd);
	cmd = ft_strjoin("/", cmd);
	while (data->path && data->path[i] != NULL)
	{
		tmp_path = ft_strjoin(data->path[i], cmd);
		if (access(tmp_path, F_OK | X_OK) == 0)
			return (free(cmd), tmp_path);
		free(tmp_path);
		i++;
	}
	free(cmd);
	return (NULL);
}
