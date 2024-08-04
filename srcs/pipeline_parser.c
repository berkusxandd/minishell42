#include "../includes/minishell.h"


t_pipeline *parser(char *input)
{
	t_nns *nns;
	t_pipeline *pipeline;

	pipeline = pipeline_init();
	if (!pipeline)
		return NULL;
	nns = nns_init(input);
	if (!nns)
	{
		free_pipeline(pipeline);
		return NULL;
	}
	pipeline->outfiles = tokenization(&nns,'>');
	if (!pipeline->outfiles)
	{
		free_pipeline(pipeline);
		return NULL;
	}
	pipeline->infiles = tokenization(&nns, '<');
	if (!pipeline->infiles)
	{
		free_pipeline(pipeline);
		return NULL;
	}
	pipeline->here_docs = tokenization(&nns, -1);
	if (!pipeline->here_docs)
	{
		free_pipeline(pipeline);
		return NULL;
	}
	pipeline->outfiles_ext = tokenization(&nns, -2);
	if (!pipeline->outfiles_ext)
	{
		free_pipeline(pipeline);
		return NULL;
	}
	pipeline->cmd = cmd_quote_parse(nns->newstr);
	free(nns->newstr);
	free(nns);
	return pipeline;
}


int pipelines_creator(t_all_pipelines *all_pipes, char *input)
{
	char **pipelines_str = ft_split(input, '|');
	if (!pipelines_str)
		return 0;
	int pipe_counter = count_tokens(input, '|');
	all_pipes->pipelines = ft_calloc(sizeof(t_pipeline), (pipe_counter + 2));
	if (!all_pipes->pipelines)
		return(error_0(pipelines_str));
	int i;
	i = 0;
	while(pipelines_str[i])
	{
		all_pipes->pipelines[i] = parser(pipelines_str[i]);
		if (!all_pipes->pipelines[i])
			return(error_0(pipelines_str));
		free(pipelines_str[i]);
		i++;
	}
	free(pipelines_str);
	all_pipes->pipelines[i] = NULL;
	return 1;
}
