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

t_vector2 quote_handler(char *str)
{
	t_vector2 v2;
	int quote_type;
	int old_quote_type;

	v2.i = 0;
	v2.j = 0;
	quote_type = 0;
	while (str[v2.i])
	{
		old_quote_type = quote_type;
		quote_type = quote_check(str[v2.i],quote_type);
		if(old_quote_type != quote_type && quote_type != 0)
			v2.j = v2.i;
		if(old_quote_type != quote_type && quote_type == 0)
		{
			v2.j -= 1;
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

char *quote_parser(char *str)
{
	t_vector2 v2;
	int quote_count;
	quote_count = count_quotes(str);
	char *quote_parsed_str;
	quote_parsed_str = malloc(sizeof(char) * (ft_strlen(str) - quote_count * 2 + 1));
	v2 = quote_handler(str);
	return quote_parsed_str;
}
