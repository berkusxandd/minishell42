/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bince < bince@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 17:29:40 by mel-yand          #+#    #+#             */
/*   Updated: 2024/08/08 17:44:35 by bince            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# define READ 0
# define WRITE 1

typedef struct s_nns
{
	char	*name;
	char	*newstr;
} t_nns;

typedef struct s_pipeline
{
	char	**cmd;
	char	**infiles;
	char	**outfiles;
	char	**outfiles_ext;
	char	**here_docs;
	char	*here_filename;
	int		infile_fd;
	int		outfile_fd;
	pid_t	pid;
	int		pipefd[2];
} t_pipeline;


typedef struct s_all_pipelines
{
	t_pipeline	**pipelines;
} t_all_pipelines;

typedef struct s_vector2
{
	int i;
	int j;
} t_vector2;

typedef struct s_data
{
	char			**path;
	t_list			*env;
	char			**env_array;
	int				status;
	t_all_pipelines	*all_pipes;
	int				index;
	int signal;
}	t_data;

#endif
