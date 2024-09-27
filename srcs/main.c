/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bince < bince@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 12:52:21 by bince             #+#    #+#             */
/*   Updated: 2024/09/27 11:47:18 by bince            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>

t_signals	g_signals = {0};

int	pipe_check(t_all_pipelines *all_pipes)
{
	int	i;

	i = 0;
	while (all_pipes->pipelines[i])
	{
		if (all_pipes->pipelines[i]->cmd)
		{
			if (all_pipes->pipelines[i]->cmd[0] == NULL
				&& (all_pipes->pipelines[i]->infiles[0] == NULL
					&& all_pipes->pipelines[i]->outfiles[0] == NULL
					&& all_pipes->pipelines[i]->here_docs[0] == NULL))
				return (-1);
		}
		i++;
	}
	return (1);
}

void	execute_input(char *input, t_data *core)
{
	int	pipelines_succeed;

	core->all_pipes = ft_calloc(sizeof(t_all_pipelines), 1);
	if (core->all_pipes)
	{
		pipelines_succeed = pipelines_creator(core->all_pipes, input);
		free(input);
		if (pipelines_succeed == 0)
			error_pipeline_malloc(core);
		else
		{
			if (pipe_check(core->all_pipes) != -1)
			{
				execution(core);
				if (g_signals.here_doc_quit == 1)
					g_signals.here_doc_quit = 0;
			}
			else
				error_empty_pipe(core);
			free_all_pipelines(core->all_pipes);
		}
	}
	else
		ft_putstr_fd("pipeline malloc error\n", 1);
}

void	exit_handler(t_data *core)
{
	int	exit_status;

	exit_status = core->status;
	free_env(&core->env);
	free_tab(core->path);
	clear_history();
	exit(exit_status);
}

int	ms_loop(t_data *core)
{
	char	*input_raw;
	int		input_raw_check;
	char	*input;

	g_signals.cmd_quit = 0;
	input_raw = readline("minishell> ");
	input_raw_check = input_raw_checks(input_raw, core);
	if (input_raw_check != 1)
		return (-1);
	if (input_quote_valid(input_raw) != 0)
		ft_putstr_fd("(d)quote error\n", 1);
	else if (input_raw[0] == '|')
		error_empty_pipe(core);
	else
	{
		if (input_raw[0] != '\0')
		{
			input = input_prep(input_raw, *core);
			if (input)
				execute_input(input, core);
			else
				ft_putstr_fd("malloc error.\n", 2);
		}
	}
	return (free(input_raw), 1);
}

int	main(int argc, char **argv, char **env)
{
	t_data	core;
	int		data_init;

	(void)argc;
	(void)argv;
	(void)env;
	data_init = init_data(&core, env);
	if (data_init == 0)
	{
		signal_init(&core);
		while (core.signal != 0)
		{
			if (ms_loop(&core) == -1)
				break ;
		}
	}
	exit_handler(&core);
}
