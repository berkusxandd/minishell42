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
	int *outfiles_fd;
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

typedef struct s_core
{
	t_all_pipelines *all_pipelines;

}t_core;

typedef struct s_list
{
	char			*var;
	char			*value;
	struct s_list	*prev;
	struct s_list	*next;
}t_list;
typedef struct s_data
{
	char			**path;
	t_list			*env;
	char			**env_array;
	int				status;
	t_all_pipelines	*all_pipes;
}	t_data;


int is_set(char c);
int is_token(char c);
char *parse(char *input);
char *delete_part(char *input, int i, int j,int l);
char *cut_str(char *input, int i, int j);
char  **tokenization(t_nns **nns, char token);
int count_tokens(char *input, char token);
t_nns *gen_token(t_nns *nns_old, char token);
int quote_check(char c, int quote_type);
int pipelines_creator(t_all_pipelines *all_pipes, char *input);
t_pipeline *parser(char *input);
void free_all_pipelines(t_all_pipelines *all_pipelines);
void free_pipeline(t_pipeline *pipeline);
void error_exit();
char *two_signs_handler(char *input);
t_pipeline *pipeline_init();
t_nns *nns_init(char *input);
int count_quotes(char *str);
char *quote_parser(char *str);
void free_str_tab(char **tab);
void free_nns(t_nns *nns);
int error_0(char **str_tab);

t_list	*ft_lstnew(char *var, char *value);
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstnew(char *var, char *value);
void	init_data(t_data *data, char **env);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_env(t_list *env, char **cmd);
char *get_value(char *varname, t_list *env);
char *parse_input_args(char *input,t_list *env);
void	free_env(t_list **env);

#endif
