#include "../../includes/minishell.h"

char	*get_namedoc(void)
{
	int		nb;
	int		loop;
	char	*name;
	char	*num;

	loop = 1;
	nb = 0;
	while (loop == 1)
	{
		num = ft_itoa(nb);
		name = ft_strjoin("/tmp/.heredoc_", num);
		free(num);
		if (access(name, F_OK) != 0)
			loop = 0;
		else
		{
			nb++;
			free(name);
		}
	}
	return (name);
}

void	sig_heredoc(int status)
{
	(void)status;
	rl_replace_line("", 0);
	rl_redisplay();
	rl_done = 1;
	g_signals.here_doc_quit = 1;
}

void handle_heredoc(char *delim, int fd)
{
	char	*line;

	signal(SIGINT, sig_heredoc);
	g_signals.here_doc_quit = 0;
	rl_catch_signals = 0;
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			ft_putstr_fd("minishell: here_doc: called end-of-line (ctrl-d)\n",
				2);
			break ;
		}
		if ((!ft_strncmp(line, delim,ft_strlen(line)) && ft_strlen(line) > 0) || g_signals.here_doc_quit == 1)
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	signal(SIGINT, handle_sigint);
	lseek(fd, 0, SEEK_SET);
}
void	heredocs(t_pipeline *pipeline)
{
	int		i;
	char	*filename;
	int		fd;

	i = 0;
	while (pipeline->here_docs[i])
	{
		filename = get_namedoc();
		fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (fd == -1)
		{
			perror("Error open");
			free(filename);
			return;
		}
		handle_heredoc(pipeline->here_docs[i], fd);
		if (g_signals.here_doc_quit)
        {
            close(fd);
            unlink(filename);
            free(filename);
            return;
        }
		if (pipeline->here_docs[i + 1] != NULL)
		{
			close(fd);
			unlink(filename);
			free(filename);
		}
		else
		{
			pipeline->infile_fd = fd;
			pipeline->here_filename = filename;
		}
		i++;
	}
}
