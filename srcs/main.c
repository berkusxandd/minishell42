#include "../includes/minishell.h"
#include <stdio.h>

int g_interrupted = 0;
t_nns	*nns_init(char *input)
{
	t_nns	*nns;

	nns = malloc(sizeof(t_nns));
	if (nns == NULL)
		return (NULL);
	nns->name = NULL;
	nns->newstr = ft_strdup(input);
	if (!nns->newstr)
		return (NULL);
	return (nns);
}

t_pipeline	*pipeline_init(void)
{
	t_pipeline	*pipeline;

	pipeline = malloc(sizeof(t_pipeline));
	if (pipeline == NULL)
		return (NULL);
	pipeline->cmd = NULL;
	pipeline->infiles = NULL;
	pipeline->outfiles = NULL;
	pipeline->here_docs = NULL;
	pipeline->here_filename = NULL;
	pipeline->infile_fd = 0;
	pipeline->outfile_fd = 1;
	return (pipeline);
}

char *two_signs_handler_2(int i, char *new_input, int q_type)
{
	if (new_input[i] == '>' && new_input[i + 1] == '>' && q_type == 0)
	{
		new_input[i] = -2;
		new_input[i + 1] = ' ';
	}
	else if (new_input[i] == '$' && q_type != 1)
		new_input[i] = -3;
	return new_input;
}

char	*two_signs_handler(char *input)
{
	int		i;
	char	*new_input;
	int		q_type;

	new_input = ft_strdup(input);
	if (!new_input)
		return (NULL);
	q_type = 0;
	if (!new_input)
		return (NULL);
	i = 0;
	while (new_input[i + 1])
	{
		q_type = quote_check(new_input[i], q_type);
		if (new_input[i] == '<' && new_input[i + 1] == '<' && q_type == 0)
		{
			new_input[i] = -1;
			new_input[i + 1] = ' ';
		}
		new_input = two_signs_handler_2(i,new_input,q_type);
		i++;
	}
	return (new_input);
}

void	error_exit(void)
{
	exit(-1);
}

int	input_quote_valid(char *input)
{
	int	i;
	int	q_type;

	i = 0;
	q_type = 0;
	while (input[i])
	{
		q_type = quote_check(input[i], q_type);
		i++;
	}
	return (q_type);
}

void	handle_sigint(int sig)
{
    (void)sig; 
    rl_on_new_line();
    rl_replace_line("", 0);
    ft_putstr_fd("\n", 1);
	g_interrupted = 1;
}

char	*input_prep(char *input_raw, t_data core)
{
	char	*input;

	input = two_signs_handler(input_raw);
	if (!input)
		return (NULL);
	input = parse_input_args(input, core);
	if (!input)
		return (NULL);
	return (input);
}

void signal_init(t_data *core)
{
	core->signal = 1;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_sigint);
	rl_catch_signals = 0;
}

void execute_input(char *input, t_data *core)
{
	int pipelines_succeed;
	core->all_pipes = ft_calloc(sizeof(t_all_pipelines), 1);
	if (core->all_pipes)
	{
		pipelines_succeed = pipelines_creator(core->all_pipes, input);
		free(input);
		if (pipelines_succeed == 0)
		{
			ft_putstr_fd("pipeline malloc error\n", 1);
			free_all_pipelines(core->all_pipes);
		}
		else
		{
            execution(core);
            free_all_pipelines(core->all_pipes);
		}
	}
	else
		ft_putstr_fd("pipeline malloc error\n", 1);
}

int input_raw_checks(char *input_raw, t_data *core)
{
	if (input_raw == NULL)
	{
		ft_putstr_fd("exiting...\n", 1);
		core->signal = 0;
		return 0;
	}
	else if (is_exit(input_raw) == 0)
	{
		free(input_raw);
		core->signal = 0;
		return -1;
	}
	else
	{
		if (*input_raw)
			add_history(input_raw);
		return 1;
	}
}

void exit_handler(t_data *core)
{
	free_env(&core->env);
	free_tab(core->path);
	clear_history();
}

int ms_loop(t_data *core)
{
	char *input_raw;
	int input_raw_check;
	char *input;
	g_interrupted = 0;
	input_raw = readline("minishell> ");
	input_raw_check = input_raw_checks(input_raw, core);
	if (input_raw_check != 1 || g_interrupted)
	{
			free(input_raw);
			return -1;
	}
	if (input_quote_valid(input_raw) != 0)
		ft_putstr_fd("(d)quote error\n", 1);
	else
	{
		if (input_raw[0] != '\0')
		{
			input = input_prep(input_raw, *core);
			if (input)
				execute_input(input, core);
			else
				ft_putstr_fd("malloc error.\n",2);
		}
	}
	free(input_raw);
	return 1;
}

int	main(int argc, char **argv, char **env)
{
	t_data			core;

	(void)argc;
	(void)argv;
	(void)env;
	init_data(&core, env);
	signal_init(&core);
	while (core.signal != 0)
	{
		if (ms_loop(&core) == -1)
			break;
	}
	exit_handler(&core);
}
