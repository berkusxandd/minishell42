#include "../includes/minishell.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (lst == NULL || new == NULL)
		return ;
	if (*lst != NULL)
	{
		last = ft_lstlast(*lst);
		last->next = new;
		new->prev = last;
	}
	else
		*lst = new;
}

void	free_env(t_list **env)
{
	t_list *cur;
	t_list *prev;

	cur = *env;
	while (cur)
	{
		prev = cur;
		cur = cur->next;
		free(prev->var);
		free(prev->value);
		free(prev);
	}
}

t_list	*ft_lstnew(char *var, char *value)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (new == NULL)
		return (NULL);
	new->var = NULL;
	new->value = NULL;
	if (var)
		new->var = ft_strdup(var);
	if (value)
		new->value = ft_strdup(value);
	new->prev = NULL;
	new->next = NULL;
	return (new);
}
