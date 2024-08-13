/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bince < bince@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 06:47:52 by bince             #+#    #+#             */
/*   Updated: 2024/08/13 06:47:53 by bince            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_wordlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && is_set(str[i]) == 0)
		++i;
	return (i);
}

static char	*word_dupe(char *str)
{
	int		i;
	int		len;
	char	*word;

	i = 0;
	len = ft_wordlen(str);
	word = malloc(sizeof(char) * (len + 1));
	if (!word)
	{
		free(word);
		return (NULL);
	}
	word[len] = '\0';
	while (i < len)
	{
		word[i] = str[i];
		++i;
	}
	return (word);
}

static void	fill_words(char **array, char *str)
{
	int	word_index;
	int	i;

	word_index = 0;
	i = 0;
	while (*str != '\0')
	{
		while (is_set(*str) == 1)
			++str;
		if (*str == '\0')
			break ;
		array[word_index] = word_dupe(str);
		if (!array[word_index])
		{
			while (i < word_index)
				free(array[i++]);
			free(array);
			return ;
		}
		++word_index;
		while (*str != '\0' && is_set(*str) == 0)
			++str;
	}
	array[word_index] = NULL;
}

static int	count_words(char *str)
{
	int	num_words;

	num_words = 0;
	while (*str != '\0')
	{
		while (is_set(*str) == 1)
			++str;
		if (*str != '\0')
		{
			++num_words;
			while (*str != '\0' && is_set(*str) == 0)
				++str;
		}
	}
	return (num_words);
}

char	**ft_split_str(char const *str)
{
	int		num_words;
	char	**array;

	if (!str)
		return (NULL);
	num_words = count_words((char *)str);
	array = malloc(sizeof(char *) * (num_words + 1));
	if (!array)
		return (NULL);
	fill_words(array, (char *)str);
	return (array);
}
