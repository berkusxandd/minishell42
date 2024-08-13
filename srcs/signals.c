#include "../includes/minishell.h"

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

void	signal_init(t_data *core)
{
	core->signal = 1;
	g_signals.cmd_quit = 0;
	rl_event_hook = sig_event;
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}
