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

int put_contents_to_nns(t_nns *nns, int i, int j, int k)
{
	char *tmp;
	int extended;

	if (nns->newstr[k] == -2 || nns->newstr[k] == '>')
		extended = 2;
	else
		extended = 1;
	char *wo_quote = cut_str(nns->newstr, i, j , extended);
	if (extended == 2)
	{
		if (nns->newstr[k] == -2)
			wo_quote[0] = 'x';
		else
			wo_quote[0] = '0';
	}
	nns->name = quote_parser(wo_quote);
	if (!nns->name)
	{
		free_nns(nns);
		return 0;
	}
	tmp = nns->newstr;
	nns->newstr = delete_part(tmp,i,j,k);
	free(tmp);
	if (!nns->newstr)
	{
	free_nns(nns);
	return 0;
	}
	return 1;
}

int space_skip(t_nns *nns, int *quote_type, int i,int k)
{
	int local_quote_type;

	local_quote_type = *quote_type;
	*quote_type = quote_check(nns->newstr[i], local_quote_type);
	local_quote_type = *quote_type;
	while(is_set(nns->newstr[i]) == 1 && nns->newstr[i] && local_quote_type == 0)
		i++;
	if (k != i - 1)
		*quote_type = quote_check(nns->newstr[i], local_quote_type);
	return i;
}

int is_cur_token(char c, char token)
{
	if (token == '>' || token == -2)
	{
		if (c == '>' || c == -2)
			return 1;
		else
			return 0;
	}
	else
		return (c == token);
}

t_nns *find_token(t_nns *nns, char token)
{
	int quote_type;
	int i;
	int j;
	int k;

	i = 0;
	quote_type = 0;
	while (nns->newstr[i])
	{
		quote_type = quote_check(nns->newstr[i], quote_type);
		if (is_cur_token(nns->newstr[i],token) != 0 && quote_type == 0) //if (nns->newstr[i] == token && quote_type == 0)
		{
			k = i++;
			i = space_skip(nns,&quote_type,i,k);
			j = i;
			while(nns->newstr[i] != '\0' && ( (quote_type != 0) || (is_token(nns->newstr[i]) == 0 && is_set(nns->newstr[i]) == 0)))
				quote_type = quote_check(nns->newstr[++i], quote_type);
			if (i != j)
			{
				if (put_contents_to_nns(nns,i,j,k) == 0)
					return NULL;	
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
		if(is_cur_token(input[i],token) != 0 && quote_type == 0)
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
