#include "../includes/minishell.h"

t_pipeline	*parser_2(t_pipeline *pipeline, t_nns **nns)
{
	pipeline->outfiles = tokenization(nns, '>');
	if (!pipeline->outfiles)
	{
		free_pipeline(pipeline);
		return (NULL);
	}
	pipeline->infiles = tokenization(nns, '<');
	if (!pipeline->infiles)
	{
		free_pipeline(pipeline);
		return (NULL);
	}
	pipeline->here_docs = tokenization(nns, -1);
	if (!pipeline->here_docs)
	{
		free_pipeline(pipeline);
		return (NULL);
	}
	pipeline->cmd = cmd_quote_parse((*nns)->newstr);
	if (!pipeline->cmd)
	{
		free_pipeline(pipeline);
		return (NULL);
	}
	return (pipeline);
}
t_pipeline	*parser(char *input)
{
	t_nns		*nns;
	t_pipeline	*pipeline;

	pipeline = pipeline_init();
	if (!pipeline)
		return (NULL);
	nns = nns_init(input);
	if (!nns)
	{
		free_pipeline(pipeline);
		return (NULL);
	}
	pipeline = parser_2(pipeline, &nns);
	free(nns->newstr);
	free(nns);
	if (!pipeline)
		return (NULL);
	return (pipeline);
}

int	pipelines_creator(t_all_pipelines *all_pipes, char *input)
{
	char	**pipelines_str;
	int		i;
	int		pipe_counter;

	input = parse_pipes_in_quotes(input);
	pipelines_str = ft_split(input, '|');
	pipelines_str = deparse_pipes(pipelines_str);
	if (!pipelines_str)
		return (0);
	pipe_counter = count_tokens(input, '|');
	all_pipes->pipelines = ft_calloc(sizeof(t_pipeline), (pipe_counter + 2));
	if (!all_pipes->pipelines)
		return (error_0(pipelines_str));
	i = 0;
	while (pipelines_str[i])
	{
		all_pipes->pipelines[i] = parser(pipelines_str[i]);
		if (!all_pipes->pipelines[i])
			return (error_0(pipelines_str));
		free(pipelines_str[i]);
		i++;
	}
	free(pipelines_str);
	all_pipes->pipelines[i] = NULL;
	return (1);
}
