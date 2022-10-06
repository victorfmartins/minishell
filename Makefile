ifneq (,$(findstring xterm,${TERM}))
	GREEN        := $(shell tput -Txterm setaf 2)
	YELLOW       := $(shell tput -Txterm setaf 3)
	RESET := $(shell tput -Txterm sgr0)
endif

define GIT =
	git add .
	git status
	read -p "${YELLOW}Commit Message:${RESET}" commit_message
	echo $$commit_message
	read -p "${YELLOW}Branch:${RESET}" branch
	git commit -m "$$commit_message"
	git push origin $$branch
endef

NAME = minishell

CC = cc

WFLAGS = -Wall -Werror -Wextra

READ_FLAG = -lreadline

LIBFT = libft.a

SRC =	minishell.c prompt.c clear_staff.c envp_lst/alloc_env.c \
		envp_lst/print_env.c envp_lst/add_back.c envp_lst/last_var.c \
		envp_lst/create_var.c envp_lst/get_env.c \
		table_rows.c exec/process_cares.c exec/cmd_verifycation.c \
		exec/cmd_execution.c

OBJ = $(SRC:.c=.o)

all: $(NAME)
	@make clean

$(NAME): $(OBJ) $(LIBFT)
	@echo "$(GREEN)creating ./minishell$(RESET)"
	@$(CC) $(WFLAGS) $(READ_FLAG) $(OBJ) -L ./ -lft -o $(NAME)

%.o: %.c
	@$(CC) $(WFLAGS) -c $< -o $@

$(LIBFT):
	make -C libft

re: fclean all

fclean: clean
	rm -rf $(NAME)

clean:
	@rm -rf *.o
	@rm -rf envp_lst/*.o
	@rm -rf exec/*.o

fclean_all: fclean
	make fclean -C libft

commit: fclean_all
	@$(GIT)

.PONHY: re fclean clean all

.ONESHELL:
