#include "../../includes/minishell.h"

void heredocs_2(t_pipeline *pipeline, int *i, int fd, char *filename)
{
	int tmp_i;

	tmp_i = *i;
	if (pipeline->here_docs[tmp_i + 1] != NULL)
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
	*i = tmp_i + 1;
}
