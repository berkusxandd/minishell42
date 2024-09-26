/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bince < bince@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 13:08:29 by mel-yand          #+#    #+#             */
/*   Updated: 2024/08/13 15:21:08 by bince            ###   ########.fr       */
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
# include <limits.h>
# include "../Libft/libft.h"
# include "./struct.h"
# include "./builtins.h"
# include "./execution.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

int			init_data(t_data *data, char **env);

//--------------------------------------------------//
//						UTILS						//
//--------------------------------------------------//

void		free_tab(char **tab);
void		free_all(t_data *data);
int			count_str(char **str);
int			count_list(t_list *lst);
t_list		*find(t_data *data, char *varname);
void		free_env(t_list **env);
void		free_exit(t_data *data, int err);

//--------------------------------------------------//
//						BERKE <3					//
//--------------------------------------------------//

int			is_set(char c);
int			is_token(char c);
char		*parse(char *input);
char		*delete_part(char *input, int i, int j, int l);
char		*cut_str(char *input, int i, int j, int extended);
char		**tokenization(t_nns **nns, char token);
int			count_tokens(char *input, char token);
t_nns		*gen_token(t_nns *nns_old, char token);
int			quote_check(char c, int quote_type);
int			pipelines_creator(t_all_pipelines *all_pipes, char *input);
t_pipeline	*parser(char *input);
void		free_all_pipelines(t_all_pipelines *all_pipelines);
void		free_pipeline(t_pipeline *pipeline);
void		error_exit(void);
char		*two_signs_handler(char *input);
t_pipeline	*pipeline_init(void);
t_nns		*nns_init(char *input);
int			count_quotes(char *str);
char		*generate_str_wo_quotes(char *str, int *quote_indexes);
int			*write_quote_indexes(char *str);
char		*quote_parser(char *str);
void		free_str_tab(char **tab);
void		free_nns(t_nns *nns);
int			error_0(char **str_tab);
void		read_input(void);
int			is_exit(char *str);
char		**cmd_quote_parse(char *str);

char		*parse_input_args(char *input, t_data env);
char		*parse_space_in_quotes(char *str);
char		**deparse_spaces(char **parsed);
char		**deparse_pipes(char **parsed);
char		*parse_pipes_in_quotes(char *str);
t_pipeline	*pipeline_init(void);
t_nns		*nns_init(char *input);
int			input_quote_valid(char *input);
char		*input_prep(char *input_raw, t_data core);
int			input_raw_checks(char *input_raw, t_data *core);
char		*two_signs_handler(char *input);
char		*two_signs_handler_2(int i, char *new_input, int q_type);
void		handle_sigint(int sig);
char		**ft_split_str(char const *str);
int			is_cur_token(char c, char token);
char		**error_2(char **tokens);
char		**error_1(char **tokens, t_nns *nns);
char		*extend_outfile(t_nns *nns, int i, int j, int k);
void		index_arranger(t_nns *nns, int *i, int *j, int quote_type);
int			space_skip(t_nns *nns, int *quote_type, int i, int k);
char		**calloc_token_array(t_nns **nns, char token, int *token_count);
char		*put_tokens_in_array(t_nns **nns, int i, char **tokens);
int			count_tokens(char *input, char token);
void		handle_sigint(int sig);
void		signal_init(t_data *core);
int			sig_event(void);
int			arg_conditions(char c);
void		error_empty_pipe(t_data *core);
void		error_pipeline_malloc(t_data *core);
void		heredocs_2(t_pipeline *pipeline, int *i, int fd, char *filename);
int			*write_quote_indexes(char *str);
int			is_quote_index(int i, int *quote_indexes);
t_vector2	quote_handler(char *str, int i);
char		*put_str_in_str_utils(char *dest, char *parsed_str, int j);
char		*var_digit(char *var_name, char *parsed_str, int j);
char		*put_str_in_str(char *dest, char *source, int start_index,
				int end_index);
#endif
