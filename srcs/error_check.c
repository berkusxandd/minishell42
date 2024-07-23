#include "../includes/minishell.h"

void free_str_tab(char **tab)
{
	int i;

	i = 0;
	while(tab[i])
		free(tab[i++]);
	free(tab);
}

int error_0(char **str_tab)
{
	free_str_tab(str_tab);
	return 0;
}
