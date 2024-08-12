#include "../includes/minishell.h"

char *two_signs_handler_2(int i, char *new_input, int q_type)
{
	if (new_input[i] == '>' && new_input[i + 1] == '>' && q_type == 0)
	{
		new_input[i] = -2;
		new_input[i + 1] = ' ';
	}
	else if (new_input[i] == '$' && q_type != 1)
		new_input[i] = -3;
	return new_input;
}

char	*two_signs_handler(char *input)
{
	int		i;
	char	*new_input;
	int		q_type;

	new_input = ft_strdup(input);
	if (!new_input)
		return (NULL);
	q_type = 0;
	if (!new_input)
		return (NULL);
	i = 0;
	while (new_input[i + 1])
	{
		q_type = quote_check(new_input[i], q_type);
		if (new_input[i] == '<' && new_input[i + 1] == '<' && q_type == 0)
		{
			new_input[i] = -1;
			new_input[i + 1] = ' ';
		}
		new_input = two_signs_handler_2(i,new_input,q_type);
		i++;
	}
	return (new_input);
}


int	input_quote_valid(char *input)
{
	int	i;
	int	q_type;

	i = 0;
	q_type = 0;
	while (input[i])
	{
		q_type = quote_check(input[i], q_type);
		i++;
	}
	return (q_type);
}

char	*input_prep(char *input_raw, t_data core)
{
	char	*input;

	input = two_signs_handler(input_raw);
	if (!input)
		return (NULL);
	input = parse_input_args(input, core);
	if (!input)
		return (NULL);
	return (input);
}

int input_raw_checks(char *input_raw, t_data *core)
{
	if (input_raw == NULL)
	{
		ft_putstr_fd("exiting...\n", 1);
		core->signal = 0;
		return 0;
	}
	else if (is_exit(input_raw) == 0)
	{
		free(input_raw);
		core->signal = 0;
		return -1;
	}
	else
	{
		if (*input_raw)
			add_history(input_raw);
		return 1;
	}
}
