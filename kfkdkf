NAME = minishell
SRCS = ./srcs/main.c  ./srcs/char_checks.c ./srcs/pipeline_parser.c ./srcs/quote_handler.c ./srcs/str_manipulations.c ./srcs/tokenization.c ./srcs/error_check.c ./srcs/expand_vars.c  ./srcs/ft_cmd_split.c ./srcs/free_all_pipelines.c  \
	   srcs/builtins/cd/cd.c\
		srcs/builtins/echo/echo.c\
		srcs/builtins/env/env.c\
		srcs/builtins/export/export.c\
		srcs/builtins/export/export_utils.c\
		srcs/builtins/pwd/pwd.c\
		srcs/builtins/unset/unset.c\
		srcs/init/init_data.c\
		srcs/utils/free_fonction.c\
		srcs/executions/builtin_exec.c\
		srcs/executions/file_handler.c\
		srcs/executions/init_exec.c\
		srcs/executions/utils_exec.c\
		srcs/executions/utils_pipeline.c
OBJS_DIR = ./objs
OBJS = $(SRCS:./srcs/%.c=$(OBJS_DIR)/%.o)
LIBFT = ./Libft/libft.a
CC = gcc
CFLAGS = -Wall -Werror -Wextra
RM = rm -rf

GREEN = \033[0;92m
BLUE = \033[0;94m

all: makelibs $(NAME)

makelibs:
	@make bonus -C ./Libft
	@echo "$(BLUE)**libft compiled"

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

$(OBJS_DIR)/%.o: ./srcs/%.c | $(OBJS_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(LIBFT) -lreadline -o $(NAME)
	@echo "$(GREEN)minishell compiled"

clean:
	$(RM) $(OBJS_DIR)
	@make clean -C ./Libft

fclean: clean
	$(RM) $(NAME)
	@make fclean -C ./Libft

re: fclean all
