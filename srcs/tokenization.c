#include "../includes/minishell.h"

t_nns *gen_token(t_nns *nns_old, char token)
{
	int i;
	int j;
	int k;

	t_nns *nns;
	int quote_type;
	quote_type = 0;
	char *newstr = ft_strdup(nns_old->newstr);
	nns = nns_init(newstr);
	free(nns_old->name);
	free(nns_old->newstr);
	free(nns_old);
	i = 0;
	while (newstr[i])
	{
		quote_type = quote_check(newstr[i], quote_type);
		if (newstr[i] == token && quote_type == 0)
		{
			k = i;
			i++;
			quote_type = quote_check(newstr[i], quote_type);
			while(is_set(newstr[i]) == 1 && newstr[i] && quote_type == 0)
				i++;
			if (k != i - 1)
				quote_type = quote_check(newstr[i], quote_type);
			j = i;
			while(newstr[i] != '\0' && ( (quote_type != 0) || (is_token(newstr[i]) == 0 && is_set(newstr[i]) == 0)))
			{
				i++;
				quote_type = quote_check(newstr[i], quote_type);
			}
			if (i != j)
			{
				free(nns->newstr);
				nns->name = cut_str(newstr, i, j);
				nns->newstr = delete_part(newstr,i,j,k);
				free(newstr);
			}
			return nns;
		}
		i++;
	}
	return nns;
}

int count_tokens(char *input, char token)
{
	int i;
	int count;
	int quote_type = 0;
	count = 0;
	i = 0;

	while(input[i])
	{
		quote_type = quote_check(input[i], quote_type);
		if(input[i] == token && quote_type == 0)
			count++;
		i++;
	}
	return count;
}


char  **tokenization(t_nns **nns, char token)
{
	int token_count;
	int i;
	char **tokens;
	char *quote_parsed_str;
	i = 0;
	token_count = count_tokens((*nns)->newstr,token);
	tokens = malloc((token_count + 1) * sizeof(char*));
	if (!token)
		return NULL;
	while(i < token_count)
	{
		*nns = gen_token(*nns,token);
		quote_parsed_str = quote_parser((*nns)->name);
		tokens[i] = ft_strdup(quote_parsed_str);
		free(quote_parsed_str);
		i++;
	}
	tokens[i] = NULL;
	return tokens;
}
