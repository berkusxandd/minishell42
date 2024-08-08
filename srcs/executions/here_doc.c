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

void handle_heredoc(char *delim, int fd)
{
	char	*line;

	while (1)
	{
		line = readline("> "); //verif NULL EOF
		if (!line || strcmp(line, delim) == 0)
		{
			free(line);
			break;
		}
		write(fd, line, strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
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
			exit(EXIT_FAILURE);
		}
		handle_heredoc(pipeline->here_docs[i], fd);
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

/*unlink at the and of exec and free filename to*/
