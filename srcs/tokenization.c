#include "../includes/minishell.h"

void free_nns(t_nns *nns)
{
	if (nns)
	{
		free(nns->name);
		free(nns->newstr);
		free(nns);
	}
}

t_nns *find_token(t_nns *nns, char token)
{
	int quote_type;
	int i;
	int j;
	int k;
	char *tmp;
	i = 0;
	quote_type = 0;
	while (nns->newstr[i])
	{
		quote_type = quote_check(nns->newstr[i], quote_type);
		if (nns->newstr[i] == token && quote_type == 0)
		{
			k = i;
			i++;
			quote_type = quote_check(nns->newstr[i], quote_type);
			while(is_set(nns->newstr[i]) == 1 && nns->newstr[i] && quote_type == 0)
				i++;
			if (k != i - 1)
				quote_type = quote_check(nns->newstr[i], quote_type);
			j = i;
			while(nns->newstr[i] != '\0' && ( (quote_type != 0) || (is_token(nns->newstr[i]) == 0 && is_set(nns->newstr[i]) == 0)))
			{
				i++;
				quote_type = quote_check(nns->newstr[i], quote_type);
			}
			if (i != j)
			{
				nns->name = quote_parser(cut_str(nns->newstr, i, j));
				if (!nns->name)
				{
					free_nns(nns);
					return NULL;
				}
				tmp = nns->newstr;
				nns->newstr = delete_part(tmp,i,j,k);
				free(tmp);
				if (!nns->newstr)
				{
					free_nns(nns);
					return NULL;
				}
			}
			return nns;
		}
		i++;
	}
	return nns;
}

t_nns *gen_token(t_nns *nns_old, char token)
{
	t_nns *nns;
	char *newstr;

	newstr = ft_strdup(nns_old->newstr);
	free(nns_old->newstr);
	free(nns_old);
	if (!newstr)
		return NULL;
	nns = nns_init(newstr);
	free(newstr);
	if (!nns)
	{
		free(newstr);
		return NULL;
	}
	nns = find_token(nns, token);
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
		free((*nns)->name);
		if (!tokens[i])
		{
			free_str_tab(tokens);
			free_nns((*nns));
			free(nns);
			return NULL;
		}
		i++;
	}
	tokens[i] = NULL;
	return tokens;
}
