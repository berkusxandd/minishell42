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

int is_set(char c);
char *parse(char *input);
#endif
