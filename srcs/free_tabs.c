#include "../includes/minishell.h"

void free_str_tab(char **tab)
{
	int i;

	i = 0;
	while(tab[i])
		free(tab[i++]);
	free(tab);
}

void free_nns(t_nns *nns)
{
	if (nns)
	{
		free(nns->name);
		free(nns->newstr);
		free(nns);
	}
}
