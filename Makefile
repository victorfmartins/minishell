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

SRC =	minishell.c prompt.c general_utils.c clear_utils.c exit.c \
		ft_split_but_through_quotes.c \
		env_var_utils/alloc_env_hash.c \
		env_var_utils/manage_env_structure.c \
		env_var_utils/get_env_var.c \
		env_var_utils/set_exec_path.c \
		analysers/build_cmd_structure.c \
		analysers/build_cmd_structure_utils.c \
		analysers/print_structures.c \
		analysers/create_structures.c \
		analysers/clear_structures.c \
		analysers/set_cmd_attributes.c \
		analysers/parsers.c

OBJ = $(SRC:.c=.o)

all: $(NAME)
	@make clean

$(NAME): $(OBJ) $(LIBFT)
	@echo "$(YELLOW)creating ./minishell$(RESET)"
	@$(CC) $(WFLAGS) -g3 $(OBJ) $(READ_FLAG) -L ./ -lft -o $(NAME)

%.o: %.c
	@$(CC) -g3 $(WFLAGS) -c $< -o $@

$(LIBFT):
	make -C libft

re: fclean all
	@make clean

fclean: clean
	rm -rf $(NAME)

clean:
	@rm -rf *.o
	@rm -rf env_var_utils/*.o
	@rm -rf exec/*.o
	@rm -rf analysers/*.o

fclean_all: fclean
	make fclean -C libft
	make fclean -C pipex

commit: fclean_all
	@$(GIT)

.PONHY: re fclean clean all

.ONESHELL:
