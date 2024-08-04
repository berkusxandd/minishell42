int main(int argc, char **argv, char **env)
{
	char *input_raw;
	char *input;
	(void)argc;
	(void)argv;
	(void)env;
	t_data data;
	t_all_pipelines *all_pipes;
	int pipelines_succeed;

	init_data(&data, env);
    while (1)
	{
        input_raw = readline("minishell> ");
        if (input_raw == NULL) {
            printf("\nExiting...\n");
            break;
        }
        if (*input_raw) {
            add_history(input_raw);
        }
		if (is_exit(input_raw) == 0)
		{
			free(input_raw);
			break;
		}
		if (input_raw[0] != '\0')
		{
			input = two_signs_handler(input_raw);
    		free(input_raw);
			input = parse_input_args(input,data.env);
			if (input == NULL)
				error_exit();
			all_pipes = ft_calloc(sizeof(t_all_pipelines),1);
			pipelines_succeed = pipelines_creator(all_pipes, input);
			free(input);
			if (pipelines_succeed == 0)
				ft_putstr_fd("pipeline error\n",1);

			print_pipelines(all_pipes);
			free_all_pipelines(all_pipes);
		}
    }
	free_env(&(data.env));
    clear_history();
}
