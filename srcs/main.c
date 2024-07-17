#include "../includes/minishell.h"

#include <stdio.h>

int is_set(char c)
{
    if (c == 32)
        return 1;
    else
        return 0;
}

int is_token(char c)
{
	if (c == '>' || c == '<' || c == -1 || c == -2)
		return 1;
	else
		return 0;
}

char *cut_str(char *input, int i, int j)
{
	int len;
	int k;

	char *outfile_name;

	if (i == j)
		return NULL;
	len = i - j;
	k = 0;
	outfile_name = malloc(sizeof(char) * (len + 1));
	if (!outfile_name)
		return NULL;
	while(j < i)
	{
		outfile_name[k] = input[j];
		j++;
		k++;
	}
	outfile_name[k] = '\0';
	return outfile_name;
}

char *delete_part(char *input, int i, int j,int l)
{
	int len;
	char *newstr;
	int k;

	if (i == j)
		return NULL;
	k = 0;
	len = ft_strlen(input);
	newstr = malloc((len + 1) * sizeof(char));
	if (!newstr)
		return NULL;
	while(input[k])
	{
		if ((k >= j && k < i) || k == l)
			newstr[k] = ' ';
		else
			newstr[k] = input[k];
		k++;
	}
	newstr[k] = '\0';
	return newstr;
}
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

int quote_check(char c, int quote_type)
{
	if (c == 39 && quote_type == 0)
		return 1;
	else if (c == 39 && quote_type == 1)
		return 0;
	else if (c == 34 && quote_type == 0)
		return 2;
	else if (c == 34 && quote_type == 2)
		return 0;
	else
		return quote_type;
}

t_nns *gen_token(t_nns *nns_old, char token)
{
	int i;
	int j;
	int k;

	t_nns *nns;
	int quote_type;
	quote_type = 0;
	char *newstr = ft_strdup(nns_old->newstr);
	nns = nns_init(newstr);
	free(nns_old->name);
	free(nns_old->newstr);
	free(nns_old);
	i = 0;
	while (newstr[i])
	{
		quote_type = quote_check(newstr[i], quote_type);
		if (newstr[i] == token && quote_type == 0)
		{
			k = i;
			i++;
			quote_type = quote_check(newstr[i], quote_type);
			while(is_set(newstr[i]) == 1 && newstr[i] && quote_type == 0)
				i++;
			if (k != i - 1)
				quote_type = quote_check(newstr[i], quote_type);
			j = i;
			while(newstr[i] != '\0' && ( (quote_type != 0) || (is_token(newstr[i]) == 0 && is_set(newstr[i]) == 0)))
			{
				i++;
				quote_type = quote_check(newstr[i], quote_type);
			}
			if (i != j)
			{
				free(nns->newstr);
				nns->name = cut_str(newstr, i, j);
				nns->newstr = delete_part(newstr,i,j,k);
				free(newstr);
			}
			return nns;
		}
		i++;
	}
	return nns;
}

int count_tokens(char *input, char token)
{
	int i;
	int count;
	int quote_type = 0;
	count = 0;
	i = 0;

	while(input[i])
	{
		quote_type = quote_check(input[i], quote_type);
		if(input[i] == token && quote_type == 0)
			count++;
		i++;
	}
	return count;
}


char  **tokenization(t_nns **nns, char token)
{
	int token_count;
	int i;
	char **tokens;

	i = 0;
	token_count = count_tokens((*nns)->newstr,token);
	tokens = malloc((token_count + 1) * sizeof(char*));
	if (!token)
		return NULL;
	while(i < token_count)
	{
		*nns = gen_token(*nns,token);
		tokens[i] = ft_strdup((*nns)->name);
		i++;
	}
	tokens[i] = NULL;
	return tokens;
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
	pipeline->cmd = ft_split(nns->newstr, ' ');
	free(nns->name);
	free(nns->newstr);
	free(nns);
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
t_all_pipelines *pipelines_creator(char *input)
{
	char **pipelines_str = ft_split(input, '|');
	int pipe_counter = count_tokens(input, '|');
	free(input);
	t_all_pipelines *all_pipes;
	all_pipes = malloc(sizeof(t_all_pipelines));
	if (!pipelines_str || !all_pipes)
		return NULL;
	all_pipes->pipelines = malloc(sizeof(t_pipeline) * (pipe_counter + 2));
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

void error_exit()
{
	exit(-1);
}

void free_pipeline(t_pipeline *pipeline)
{
	int i;

	i = 0;
	while(pipeline->cmd[i])
	{
		free(pipeline->cmd[i]);
		i++;
	}
	i = 0;
	while (pipeline->infiles[i])
	{
		free(pipeline->infiles[i]);
		i++;
	}
	i = 0;
	while (pipeline->outfiles[i])
	{
		free(pipeline->outfiles[i]);
		i++;
	}
	i = 0;
	while (pipeline->outfiles_ext[i])
	{
		free(pipeline->outfiles_ext[i]);
		i++;
	}
	i = 0;
	while (pipeline->here_docs[i])
	{
		free(pipeline->here_docs[i]);
		i++;
	}
	free(pipeline);
}

void free_all_pipelines(t_all_pipelines *all_pipelines)
{
	int i;

	i = 0;
	if (all_pipelines)
	{
		if (all_pipelines->pipelines != NULL)
		{
		while (all_pipelines->pipelines[i] != NULL)
		{
			free_pipeline(all_pipelines->pipelines[i]);
			i++;
		}
		}
	free(all_pipelines);
	}
}
int main()
{
	char *test = ">a < aninfile <'a''a'   secind    < third cat Makefile >b | mem >>outfile > A > B > C > D | cat a >>extendedfile";
	char *input = two_signs_handler(test);
	if (input == NULL)
		error_exit();
	t_all_pipelines *all_pipes = pipelines_creator(input);
	printf("%s",all_pipes->pipelines[0]->infiles[1]);
	free_all_pipelines(all_pipes);
}
