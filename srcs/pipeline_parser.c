#include "../includes/minishell.h"

char **cmd_quote_parser(char *res_str)
{
	char **raw_cmds;
	char *tmp;
	int i;

	i = 0;
	raw_cmds = ft_split(res_str,' ');
	while(raw_cmds[i])
	{
		tmp = ft_strdup(raw_cmds[i]);
		free(raw_cmds[i]);
		raw_cmds[i] = quote_parser(tmp);
		free(tmp);
		i++;
	}
	return raw_cmds;
}

t_pipeline *parser(char *input)
{
	t_nns *nns;
	t_pipeline *pipeline;

	pipeline = pipeline_init();
	nns = nns_init(input);
	pipeline->outfiles = tokenization(&nns,'>');
	pipeline->infiles = tokenization(&nns, '<');
	pipeline->here_docs = tokenization(&nns, -1);
	pipeline->outfiles_ext = tokenization(&nns, -2);
	pipeline->cmd = cmd_quote_parser(nns->newstr);
	free(nns->name);
	free(nns->newstr);
	free(nns);
	return pipeline;
}

t_all_pipelines *pipelines_creator(char *input)
{
	char **pipelines_str = ft_split(input, '|');
	int pipe_counter = count_tokens(input, '|');
	t_all_pipelines *all_pipes;
	all_pipes = malloc(sizeof(t_all_pipelines));
	if (!pipelines_str || !all_pipes)
		return NULL;
	all_pipes->pipelines = malloc(sizeof(t_pipeline) * (pipe_counter + 2));///BU MALLOC LEAK
	int i;
	i = 0;
	while(pipelines_str[i])
	{
		all_pipes->pipelines[i] = parser(pipelines_str[i]);
		free(pipelines_str[i]);
		i++;
	}
	free(pipelines_str);
	all_pipes->pipelines[i] = NULL;
	return all_pipes;
}
