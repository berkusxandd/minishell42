#include "../includes/minishell.h"

char *parse_space_in_quotes(char *str)
{
    int i;
	int q_type;

    q_type = 0;
	i = 0;
	while (str[i+1])
	{
        q_type = quote_check(str[i],q_type);
        if (q_type != 0)
        {
	    	if (str[i] == ' ')
			    str[i] = -4;
        }
		i++;
	}
	return (str);
}

char **deparse_spaces(char **parsed)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (parsed[i])
    {
        j = 0;
        while (parsed[i][j])
        {
            if (parsed[i][j] == -4)
                parsed[i][j] = ' ';
            j++;
        }
        parsed[i] = quote_parser(parsed[i]);
        i++;
    }
    return parsed;
}

char **cmd_quote_parse(char *str)
{
    char **parsed_cmds;

    str = parse_space_in_quotes(str);
    parsed_cmds = ft_split(str, ' ');
    parsed_cmds = deparse_spaces(parsed_cmds);
    return parsed_cmds;
}

