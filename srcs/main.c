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
	init_data(&core, env);
        input_raw = readline("minishell> ");
    while (1)
	{
        if (input_raw == NULL) {
            ft_putstr_fd("exiting...",2);
            break;
        }
		if (is_exit(input_raw) == 0)
		{
			free(input_raw);
			break;
		}
        if (*input_raw) {
            add_history(input_raw);
        }
		if (input_raw[0] != '\0')
		{
			input = two_signs_handler(input_raw);
    		free(input_raw);
			input = parse_input_args(input,core.env);
			// if (input == NULL)
			// {
			// 	ft_putstr_fd("input null",2);
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
		}
        input_raw = readline("minishell> ");
    }
	//free_env(&(data.env));
    clear_history();
}

// int main(int argc, char **argv, char **env)
// {
// 	char *input;
// 	(void)argc;
// 	(void)argv;
// 	(void)env;
// 	t_data data;
// 	t_all_pipelines *all_pipes;
// 	int pipelines_succeed;

// 	init_data(&data, env);

// 	input = ">a < aninfile <'a''a'   secind    < third cat Makefile >b | mem >>outfile > A > B > C > D | cat a >>extendedfile";
// 	//input = "\"|||\"\";fsdlkfjslkjdf;;;\"";
// 	input = two_signs_handler(input);
// 	input = parse_input_args(input,data.env);
// 	if (input == NULL)
// 		error_exit();
// 	all_pipes = ft_calloc(sizeof(t_all_pipelines),1);
// 	pipelines_succeed = pipelines_creator(all_pipes, input);
// 	free(input);
// 	if (pipelines_succeed == 0)
// 	{
// 		ft_putstr_fd("pipeline error\n",1);
// 	}
// 	print_pipelines(all_pipes);
// 	free_all_pipelines(all_pipes);
// 	free_env(&(data.env));
//     clear_history();
// }
