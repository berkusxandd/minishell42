#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

void read_input()
{
    char *input;

    while (1) {
        input = readline("minishell> ");

        if (input == NULL) {
            printf("\nExiting...\n");
            break;
        }

        if (*input) {
            add_history(input);
        }

        if (strcmp(input, "exit") == 0) {
            free(input);
            break;
        }
        printf("You typed: %s\n", input);
        free(input);
    }
    clear_history();
    //return 0;
}
