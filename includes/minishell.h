/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bince < bince@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 13:08:29 by mel-yand          #+#    #+#             */
/*   Updated: 2024/08/06 10:22:23 by bince            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>

# include "../Libft/libft.h"
# include "./struct.h"
# include "./builtins.h"
# include "./execution.h"

#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>

void	init_data(t_data *data, char **env);

//--------------------------------------------------//
//						UTILS						//
//--------------------------------------------------//

void	free_tab(char **tab);
void	free_all(t_data *data);
int		count_str(char **str);
int		count_list(t_list *lst);
t_list	*find(t_data *data, char *varname);
void	free_env(t_list **env);

//--------------------------------------------------//
//						BERKE <3					//
//--------------------------------------------------//

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
char *generate_str_wo_quotes(char *str,int *quote_indexes);
int *write_quote_indexes(char *str);
char *quote_parser(char *str);
void free_str_tab(char **tab);
void free_nns(t_nns *nns);
int error_0(char **str_tab);
void read_input();
int is_exit(char *str);
char **cmd_quote_parse(char *str);
char *parse_input_args(char *input,t_list *env);
char *parse_space_in_quotes(char *str);
char **deparse_spaces(char **parsed);
char **deparse_pipes(char **parsed);
char *parse_pipes_in_quotes(char *str);
#endif

