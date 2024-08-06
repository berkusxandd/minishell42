#include "../includes/minishell.h"

void	ft_env(t_list *env, char **cmd)
{
	if (cmd != NULL && cmd[1] != NULL)
	{
		ft_putstr_fd("env does not take arguments\n", 2);
		/*Change status to 127*/
		return ;
	}
	while (env)
	{
		if (env->value != NULL)
		{
			ft_putstr_fd(env->var, 1);
			ft_putstr_fd("=", 1);
			ft_putstr_fd(env->value, 1);
			ft_putstr_fd("\n", 1);
		}
		env = env->next;
	}
}


void	free_tab(char **tab)
{
    int	i;

	i = 0;
	// i changed ----
	if (!tab)
		return;
	while (tab[i])
		free(tab[i++]);
	// --------------
	tab = NULL;
}

static void	shlvl_up(t_data *data, char *lvl)
{
	char	*lvlup;

	lvlup = ft_itoa(ft_atoi(lvl) + 1);
	ft_lstadd_back(&data->env, ft_lstnew("SHLVL", lvlup));
	free(lvlup);
}

static int	set_pwd(t_data *data)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	ft_lstadd_back(&data->env, ft_lstnew("PWD", cwd));
	free(cwd);
	return (1);
}

static void	check_pwd_shlvl(t_data *data, int pwd, int shlvl)
{
	if (pwd == 0)
		ft_lstadd_back(&data->env, ft_lstnew("PWD", getcwd(NULL, 0)));
	if (shlvl == 0)
		ft_lstadd_back(&data->env, ft_lstnew("SHLVL", "1"));
}

static void	init_env(t_data *data, char **env)
{
	int		i;
	char	**tmp;
	int		pwd;
	int		shlvl;

	i = 0;
	pwd = 0;
	shlvl = 0;
	while (env[i] != NULL)
	{
		tmp = ft_split(env[i], '=');
		// printf("%s\n", tmp[0]);
		if (ft_strncmp(tmp[0], "SHLVL", 6) == 0)
		{
			shlvl_up(data, tmp[1]);
			shlvl = 1;
		}
		else if(ft_strncmp(tmp[0], "PWD", 4) == 0)
			pwd = set_pwd(data);
		else if (tmp != NULL)
			ft_lstadd_back(&data->env, ft_lstnew(tmp[0], tmp[1]));
		free_tab(tmp);
		i++;
	}
	check_pwd_shlvl(data, pwd, shlvl);
}

void	init_data(t_data *data, char **env)
{
	data->status = 0;
	data->env = NULL;
	data->env_array = NULL;
	data->path = ft_split(getenv("PATH"), ':');

	if (env && *env)
		init_env(data, env);
	else
	{
		ft_lstadd_back(&data->env, ft_lstnew("PWD", getcwd(NULL, 0)));
		ft_lstadd_back(&data->env, ft_lstnew("SHLVL", "1"));
	}
}
