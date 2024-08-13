#include "../includes/minishell.h"

int	space_skip(t_nns *nns, int *quote_type, int i, int k)
{
	int	local_quote_type;

	local_quote_type = *quote_type;
	*quote_type = quote_check(nns->newstr[i], local_quote_type);
	local_quote_type = *quote_type;
	while (is_set(nns->newstr[i]) == 1 && nns->newstr[i]
		&& local_quote_type == 0)
		i++;
	if (k != i - 1)
		*quote_type = quote_check(nns->newstr[i], local_quote_type);
	return (i);
}

void	index_arranger(t_nns *nns, int *i, int *j, int quote_type)
{
	int	tmp_i;

	tmp_i = *i;
	*j = tmp_i;
	while (nns->newstr[tmp_i] != '\0' && ((quote_type != 0)
			|| (is_token(nns->newstr[tmp_i]) == 0
				&& is_set(nns->newstr[tmp_i]) == 0)))
		quote_type = quote_check(nns->newstr[++tmp_i], quote_type);
	*i = tmp_i;
}
