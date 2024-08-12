#include "../includes/minishell.h"
#include <stdio.h>

t_signals g_signals = {0};

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

void exit_handler(t_data *core)
{
	int exit_status;

	exit_status = core->status;
	free_env(&core->env);
	free_tab(core->path);
	clear_history();
	exit(exit_status);
}
int	sig_event(void)
{
    return (EXIT_SUCCESS);
}

void	handle_sigint(int sig)
{
    (void)sig;
   	write(STDIN_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_done = 1;
	g_signals.cmd_quit = 1;
}

void signal_init(t_data *core)
{
	core->signal = 1;
	g_signals.cmd_quit = 0;
	rl_event_hook = sig_event;
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}


int ms_loop(t_data *core)
{
	char *input_raw;
	int input_raw_check;
	char *input;
	g_signals.cmd_quit = 0;
	input_raw = readline("minishell> ");
	input_raw_check = input_raw_checks(input_raw, core);
	if (input_raw_check != 1)
		return -1;
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
