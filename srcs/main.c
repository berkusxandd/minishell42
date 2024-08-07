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
	pipeline->infile_fd = 0;
	pipeline->outfile_fd = 1;
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
		if (new_input[i] == '<' && new_input[i+1] == '<' && q_type == 0)
		{
			new_input[i] = -1;
			new_input[i+1] = ' ';
		}else if (new_input[i] == '>' && new_input[i+1] == '>' && q_type == 0)
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



void print_pipelines(t_all_pipelines *all_pipelines)
{
	int i = 0;
	int j = 0;
	while (all_pipelines->pipelines[i])
	{
		j = 0;
		printf("---- pipeline - %d ------  \n", i);
		printf("cmds \n");
		while (all_pipelines->pipelines[i]->cmd[j])
		{
			printf("%s\n", all_pipelines->pipelines[i]->cmd[j]);
			j++;
		}
		printf("\n");
		j = 0;
		printf("here_docs \n");
		while (all_pipelines->pipelines[i]->here_docs[j])
		{
			printf("%s\n", all_pipelines->pipelines[i]->here_docs[j]);
			j++;
		}
		j = 0;
		printf("\n");
		printf("infiles \n");
		while (all_pipelines->pipelines[i]->infiles[j])
		{
			printf("%s\n", all_pipelines->pipelines[i]->infiles[j]);
			j++;
		}
		j = 0;
		printf("\n");
		printf("outfiles \n");
		while (all_pipelines->pipelines[i]->outfiles[j])
		{
			printf("%s\n", all_pipelines->pipelines[i]->outfiles[j]);
			j++;
		}
		i++;
		printf("--------------------\n");
	}
}

int input_quote_valid(char *input)
{
	int i;
	int q_type;

	i = 0;
	q_type = 0;
	while (input[i])
	{
		q_type = quote_check(input[i], q_type);
		i++;
	}
	return q_type;
}

int main(int argc, char **argv, char **env)
{
	char *input_raw;
	char *input;
	(void)argc;
	(void)argv;
	(void)env;
	t_data core;
	t_all_pipelines *all_pipes;
	int pipelines_succeed;
   	int original_stdin = dup(STDIN_FILENO);
    int original_stdout = dup(STDOUT_FILENO);
	signal(SIGQUIT, SIG_IGN);
	init_data(&core, env);
	core.signal = 1;
	rl_catch_signals = 0;
    while (core.signal != 0)
	{
        input_raw = readline("minishell> ");
        if (input_raw == NULL) {
            ft_putstr_fd("exiting...\n",1);
			core.signal = 0;
            break;
        }
		if (is_exit(input_raw) == 0)
		{
			free(input_raw);
			core.signal = 0;
			break;
		}
        if (*input_raw) {
            add_history(input_raw);
        }
		if (input_quote_valid(input_raw) != 0)
		{
			ft_putstr_fd("(d)quote error\n",1);
		}
		else
		{
		if (input_raw[0] != '\0')
		{
			input = two_signs_handler(input_raw);
			input = parse_input_args(input,core.env);
			//ft_putstr_fd(input,2);
			// if (input == NULL)
			// {
			// 	ft_putstr_fd("input null",2;
			// 	error_exit();
			// }
			all_pipes = ft_calloc(sizeof(t_all_pipelines),1);
			pipelines_succeed = pipelines_creator(all_pipes, input);
			free(input);
			if (pipelines_succeed == 0)
				ft_putstr_fd("pipeline error\n",1);
			core.all_pipes = all_pipes;
			execution(&core);
			print_pipelines(core.all_pipes);
			dup2(original_stdin, STDIN_FILENO);
			dup2(original_stdout, STDOUT_FILENO);
			free(input_raw);
			free_all_pipelines(all_pipes);
		}
		}
	}
	free_env(&(core.env));
    clear_history();
}
