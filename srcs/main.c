#include "../includes/minishell.h"

#include <stdio.h>
t_nns *nns_init(char *input)
{
	t_nns *nns;

	nns = malloc(sizeof(t_nns));
	if (nns == NULL)
		return NULL;
	nns->name = NULL;
	nns->newstr = ft_strdup(input);
	if (!nns->newstr)
		return NULL;
	return nns;
}

t_pipeline *pipeline_init()
{
	t_pipeline *pipeline;
	pipeline = malloc(sizeof(t_pipeline));
	if (pipeline == NULL)
		return NULL;
	pipeline->cmd = NULL;
	pipeline->infiles = NULL;
	pipeline->outfiles = NULL;
	pipeline->outfiles_ext = NULL;
	pipeline->here_docs = NULL;
	return pipeline;
}

char *two_signs_handler(char *input)
{
	int i;
	char *new_input;

	if (input[0] == '\0')
		return NULL;
	new_input = ft_strdup(input);
	if (new_input == NULL)
		return NULL;
	i = 0;
	while (new_input[i+1])
	{
		if (new_input[i] == '<' && new_input[i+1] == '<')
		{
			new_input[i] = -1;
			new_input[i+1] = ' ';
		}else if (new_input[i] == '>' && new_input[i+1] == '>')
		{
			new_input[i] = -2;
			new_input[i+1] = ' ';
		}
		i++;
	}
	return (new_input);
}

void error_exit()
{
	exit(-1);
}

void free_pipeline(t_pipeline *pipeline)
{
	int i;

	i = 0;
	while(pipeline->cmd[i])
		free(pipeline->cmd[i++]);
	free(pipeline->cmd);
	i = 0;
	while (pipeline->infiles[i])
		free(pipeline->infiles[i++]);
	free(pipeline->infiles);
	i = 0;
	while (pipeline->outfiles[i])
		free(pipeline->outfiles[i++]);
	free(pipeline->outfiles);
	i = 0;
	while (pipeline->outfiles_ext[i])
		free(pipeline->outfiles_ext[i++]);
	free(pipeline->outfiles_ext);
	i = 0;
	while (pipeline->here_docs[i])
		free(pipeline->here_docs[i++]);
	free(pipeline->here_docs);
	free(pipeline);
}

void free_all_pipelines(t_all_pipelines *all_pipelines)
{
	int i;

	i = 0;
	if (!all_pipelines)
		return ;
	if (!all_pipelines->pipelines)
		return ;
	while (all_pipelines->pipelines[i] != NULL)
	{
			free_pipeline(all_pipelines->pipelines[i]);
			i++;
	}
	free(all_pipelines->pipelines);
	free(all_pipelines);
}
int main()
{
	//char *test = ">a < aninfile <'a''a'   secind    < third cat Makefile >b | mem >>outfile > A > B > C > D | cat a >>extendedfile";
	//char *test = "wc -l";
	char *test = "cat '''file1' > file2 < file3 | infile < cat | grep text >> file4 | infile < cat | wc -l | sleep 3 | wc -c > outfile";
	char *input = two_signs_handler(test);
	if (input == NULL)
		error_exit();
	t_all_pipelines *all_pipes = pipelines_creator(input);
	free(input);
	printf("%s",all_pipes->pipelines[0]->cmd[1]);
	free_all_pipelines(all_pipes);
}
