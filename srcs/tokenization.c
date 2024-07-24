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
	//free_nns(nns_old);
	if (!newstr)
		return NULL;
	nns = nns_init(newstr);
	if (!nns)
	{
		free(newstr);
		return NULL;
	}
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
				if (!nns->name)
				{
					free(newstr);
					//free_nns(nns);
					return NULL;
				}
				nns->newstr = delete_part(newstr,i,j,k);
				if (!nns->newstr)
				{
					free(newstr);
					//free_nns(nns);
					return NULL;
				}
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
	i = 0;
	token_count = count_tokens((*nns)->newstr,token);
	tokens = ft_calloc( sizeof(char*), (token_count + 1));
	if (!tokens)
		return NULL;
	while(i < token_count)
	{
		*nns = gen_token(*nns,token);
		if (!(*nns))
		{
			free_str_tab(tokens);
			return NULL;
		}
		tokens[i] = ft_strdup((*nns)->name);
		if (!tokens[i])
		{
			free_str_tab(tokens);
			//free_nns((*nns));
			//free(nns);
			return NULL;
		}
		i++;
	}
	tokens[i] = NULL;
	return tokens;
}
