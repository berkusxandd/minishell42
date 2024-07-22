#include "../includes/minishell.h"

int quote_check(char c, int quote_type)
{
	if (c == 39 && quote_type == 0)
		return 1;
	else if (c == 39 && quote_type == 1)
		return 0;
	else if (c == 34 && quote_type == 0)
		return 2;
	else if (c == 34 && quote_type == 2)
		return 0;
	else
		return quote_type;
}

t_vector2 quote_handler(char *str, int i)
{
	t_vector2 v2;
	int quote_type;
	int old_quote_type;

	v2.i = i;
	v2.j = i;
	quote_type = 0;
	while (str[v2.i])
	{
		old_quote_type = quote_type;
		quote_type = quote_check(str[v2.i],quote_type);
		if(old_quote_type != quote_type && quote_type != 0)
			v2.j = v2.i;
		if(old_quote_type != quote_type && quote_type == 0)
		{
			return v2;
		}
		v2.i++;
	}
	return v2;
}

int count_quotes(char *str)
{
	int quote_type;
	int old_quote_type;
	int quote_count;
	int i;

	i = 0;
	quote_type = 0;
	quote_count = 0;
	while (str[i])
	{
		old_quote_type = quote_type;
		quote_type = quote_check(str[i],quote_type);
		if(old_quote_type != quote_type && quote_type == 0)
			quote_count++;
		i++;
	}
	return quote_count;
}

void print_indexes(int *indexes)
{
	int i = 0;
	while (indexes[i] != -1)
	{
		printf("\n==%d==\n", indexes[i]);
		i++;
	}
}

int *write_quote_indexes(char *str)
{
	int i;

	i = 0;
	t_vector2 v2;
	int *quote_indexes;
	int quote_count;
	quote_count = count_quotes(str);
	quote_indexes = malloc(sizeof(int) * (quote_count  * 2 + 1));
	v2 = quote_handler(str,0);
	while(i<quote_count  * 2)
	{
		quote_indexes[i] = v2.i;
		i++;
		quote_indexes[i] = v2.j;
		i++;
		v2 = quote_handler(str, v2.i + 1);
	}
	quote_indexes[i] = -1;
	return (quote_indexes);
}

int is_quote_index(int i, int *quote_indexes)
{
	int j;

	j = 0;
	while(quote_indexes[j] != -1)
	{
		if (quote_indexes[j] == i)
			return 1;
		j++;
	}
	return 0;
}

char *generate_str_wo_quotes(char *str,int *quote_indexes)
{
	int i;
	int j;
	char *parsed_str;
	int quote_count;

	quote_count = count_quotes(str);
	parsed_str = malloc(sizeof(char) * (ft_strlen(str) + 1) - (quote_count * 2));

	i = 0;
	j = 0;
	while (str[i])
	{
		if (is_quote_index(i,quote_indexes) == 0)
		{
			parsed_str[j] = str[i];
			j++;
		}
		i++;
	 }
	 parsed_str[j] = '\0';
	 free(quote_indexes);
	 return parsed_str;
}

char *quote_parser(char *str)
{
	int *quote_indexes;
	quote_indexes = write_quote_indexes(str);
	char *parsed_str = generate_str_wo_quotes(str, quote_indexes);
	return parsed_str;
}
