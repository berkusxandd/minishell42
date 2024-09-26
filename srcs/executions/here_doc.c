/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bince < bince@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 13:14:04 by bince             #+#    #+#             */
/*   Updated: 2024/08/13 18:50:52 by bince            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		if (num == NULL)
			return (NULL);
		name = ft_strjoin("/tmp/.heredoc_", num);
		if (name == NULL)
			return (free(num), NULL);
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

int	here_doc_condition(char *line, char *delim)
{
	if (!ft_strncmp(line, delim, ft_strlen(line)) && ft_strlen(line) > 0)
		return (1);
	else
		return (0);
}

void	handle_heredoc(char *delim, int fd)
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
		if ((here_doc_condition(line, delim)) || g_signals.here_doc_quit == 1)
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

int	heredocs(t_pipeline *pipeline)
{
	int		i;
	char	*filename;
	int		fd;

	i = 0;
	while (pipeline->here_docs[i])
	{
		filename = get_namedoc();
		if (filename == NULL)
			return (-1);
		fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (fd == -1)
			return (open_err_hd(filename));
		handle_heredoc(pipeline->here_docs[i], fd);
		if (g_signals.here_doc_quit)
		{
			close(fd);
			unlink(filename);
			free(filename);
			return (-1);
		}
		heredocs_2(pipeline, &i, fd, filename);
	}
	return (0);
}
