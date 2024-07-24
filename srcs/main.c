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
	int q_type;
	new_input = ft_strdup(input);

	q_type = 0;
	if (!new_input)
		return NULL;
	i = 0;
	while (new_input[i+1])
	{
		q_type = quote_check(new_input[i],q_type);
		if (new_input[i] == '<' && new_input[i+1] == '<' && q_type != 1)
		{
			new_input[i] = -1;
			new_input[i+1] = ' ';
		}else if (new_input[i] == '>' && new_input[i+1] == '>' && q_type != 1)
		{
			new_input[i] = -2;
			new_input[i+1] = ' ';
		}
		else if (new_input[i] == '$' && q_type != 1)
			new_input[i] = -3;
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
	if (pipeline->cmd)
	{
		while(pipeline->cmd[i])
			free(pipeline->cmd[i++]);
	free(pipeline->cmd);
	}
	i = 0;
	if (pipeline->infiles)
	{
		while (pipeline->infiles[i])
			free(pipeline->infiles[i++]);
		free(pipeline->infiles);
	}
	i = 0;
	if (pipeline->outfiles)
	{
		while (pipeline->outfiles[i])
			free(pipeline->outfiles[i++]);
		free(pipeline->outfiles);
	}
	i = 0;
	if (pipeline->outfiles_ext)
	{
		while (pipeline->outfiles_ext[i])
			free(pipeline->outfiles_ext[i++]);
		free(pipeline->outfiles_ext);
	}
	i = 0;
	if (pipeline->here_docs)
	{
		while (pipeline->here_docs[i])
			free(pipeline->here_docs[i++]);
		free(pipeline->here_docs);
	}
	free(pipeline);
}

void free_all_pipelines(t_all_pipelines *all_pipelines)
{
	int i;

	i = 0;
	if (!all_pipelines)
		return ;
	if (all_pipelines->pipelines)
	{
	while (all_pipelines->pipelines[i] != NULL)
	{
			free_pipeline(all_pipelines->pipelines[i]);
			i++;
	}
	free(all_pipelines->pipelines);
	}
	free(all_pipelines);
}


int main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	t_data data;

	init_data(&data, env);
	//char *test = ">a < aninfile <'a''a'   secind    < third cat Makefile >b | mem >>outfile > A > B > C > D | cat a >>extendedfile";
	//char *test = "wc -l";
	char *test = "cat '''file1' $LOGNAME  $LOGNAME       | infile < cat | grep text >> file4 | infile < cat | wc -l | sleep 3 | wc -c > outfile";
	char *input = two_signs_handler(test);
	input = parse_input_args(input,data.env);
	input = quote_parser(input);
	printf("PARSED DATA : %s",input);
	int pipelines_succeed;
	if (input == NULL)
		error_exit();
	t_all_pipelines *all_pipes = ft_calloc(sizeof(t_all_pipelines),1);
	pipelines_succeed = pipelines_creator(all_pipes, input);
	free(input);
	if (pipelines_succeed != 0)
		printf("%s",all_pipes->pipelines[0]->cmd[1]);
	else
		printf("pipeline error");
	free_all_pipelines(all_pipes);
	ft_env(data.env,NULL);
	free_env(&(data.env));
	//printf("\n %s \n",get_value("LOGNAME",data.env));
}
