/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_manipulations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bince < bince@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 13:11:16 by bince             #+#    #+#             */
/*   Updated: 2024/08/13 13:11:18 by bince            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*cut_str(char *input, int i, int j, int extended)
{
	int		len;
	int		k;
	char	*outfile_name;

	if (i == j)
		return (NULL);
	len = i - j;
	k = extended - 1;
	outfile_name = malloc(sizeof(char) * (len + 2));
	if (!outfile_name)
		return (NULL);
	while (j < i)
	{
		outfile_name[k] = input[j];
		j++;
		k++;
	}
	outfile_name[k] = '\0';
	return (outfile_name);
}

char	*delete_part(char *input, int i, int j, int l)
{
	int		len;
	char	*newstr;
	int		k;

	if (i == j)
		return (NULL);
	k = 0;
	len = ft_strlen(input);
	newstr = malloc((len + 1) * sizeof(char));
	if (!newstr)
		return (NULL);
	while (input[k])
	{
		if ((k >= j && k < i) || k == l)
			newstr[k] = ' ';
		else
			newstr[k] = input[k];
		k++;
	}
	newstr[k] = '\0';
	return (newstr);
}

int	is_exit(char *str)
{
	int	len;

	if (str == NULL)
		return (1);
	len = ft_strlen(str);
	if (len != 4)
		return (1);
	return (ft_strncmp(str, "exit", 4));
}
