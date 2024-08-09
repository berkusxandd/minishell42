#include "../includes/minishell.h"

char *get_value(char *varname, t_list *env)
{
	while(env)
	{
		if (ft_strlen(varname) == ft_strlen(env->var))
		{
		if(ft_strncmp(env->var,varname,ft_strlen(varname)) == 0)
			return (env->value);
		}
		env = env->next;
	}
	return (ft_strdup(""));
}
//start index is dolar
char *put_str_in_str(char *dest, char *source, int start_index, int end_index)
{
	char *parsed_str;
	int i;
	int j;

	i = 0;
	j = 0;
	parsed_str = malloc(sizeof(char) * (ft_strlen(dest) + ft_strlen(source) + 1));
	while (dest[i])
	{
		if (i == start_index)
		{
			while(source[j - start_index])
			{
				parsed_str[j] = source[j - start_index];
				j++;
			}
			i++;
		}
		else if(i > end_index || i < start_index)
			parsed_str[j++] = dest[i++];
		else
			i++;
	}
	free(dest);
	parsed_str[j] = '\0';
	return (parsed_str);
}

char *find_val_put_str(char *parsed_str, int i, int j, t_data core)
{
	char *var_name;
	char *var_value;

	var_name = cut_str(parsed_str,i,j,1);
	if (var_name[0] == '?')
	{
		var_value = ft_itoa(core.status);
		free(var_name);
		parsed_str = put_str_in_str(parsed_str,var_value,j-1,i-1);
		return parsed_str;
	}
	else
	{
	var_value = get_value(var_name,core.env);
	free(var_name);
	parsed_str = put_str_in_str(parsed_str,var_value,j-1,i-1);
	return parsed_str;
	}
}


char *parse_input_args(char *input,t_data core)
{
	int i;
	int j;
	char *parsed_str;
	char *tmp_var_name;

	parsed_str = ft_strdup(input);
	if (!parsed_str)
		return NULL;
	i = 0;
	free(input);
	while(parsed_str[i])
	{
		if (parsed_str[i] == -3)
		{
			i++;
			j = i;
			while(parsed_str[i] && (ft_isalnum(parsed_str[i]) || parsed_str[i] == '_' ||  parsed_str[i] == '?'))
				i++;
			if (i==j)
				parsed_str[j - 1] = '$';
			else
			{
			tmp_var_name = cut_str(parsed_str,i,j,1);
			parsed_str = find_val_put_str(parsed_str,i,j,core);
			i = j - 1 + ft_strlen(get_value(tmp_var_name,core.env));
			}
		}
		else
			i++;
	}
	return parsed_str;
}


