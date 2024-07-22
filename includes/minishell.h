#ifndef MINISHELL_H
#define MINISHELL_H
#include "../Libft/libft.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>

typedef struct s_nns
{
	char *name;
	char *newstr;
} t_nns;

typedef struct s_pipeline
{
	char **infiles;
	char **outfiles;
	char **outfiles_ext;
	char **here_docs;
	char **cmd;
} t_pipeline;

typedef struct s_all_pipelines
{
	t_pipeline **pipelines;
} t_all_pipelines;

typedef struct s_vector2
{
	int i;
	int j;
} t_vector2;

typedef struct s_minishell
{

} 

int is_set(char c);
int is_token(char c);
char *parse(char *input);
char *delete_part(char *input, int i, int j,int l);
char *cut_str(char *input, int i, int j);
char  **tokenization(t_nns **nns, char token);
int count_tokens(char *input, char token);
t_nns *gen_token(t_nns *nns_old, char token);
int quote_check(char c, int quote_type);
t_all_pipelines *pipelines_creator(char *input);
t_pipeline *parser(char *input);
void free_all_pipelines(t_all_pipelines *all_pipelines);
void free_pipeline(t_pipeline *pipeline);
void error_exit();
char *two_signs_handler(char *input);
t_pipeline *pipeline_init();
t_nns *nns_init(char *input);
int count_quotes(char *str);
char *quote_parser(char *str);
#endif
