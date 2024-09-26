/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_mem_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bince < bince@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 19:33:11 by bince             #+#    #+#             */
/*   Updated: 2024/08/13 19:49:45 by bince            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*fp_fd_init(int *fd)
{
	*fd = -1;
	return (NULL);
}

int	free_fp_inc_i(int i, char *filepath)
{
	free(filepath);
	return (i + 1);
}

char	*filepath_init(char *filepath, int *fd, int i, t_pipeline *node)
{
	filepath = fp_fd_init(fd);
	filepath = get_pathfile(node->infiles[i]);
	return (filepath);
}
