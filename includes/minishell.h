/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 22:57:04 by asoler            #+#    #+#             */
/*   Updated: 2022/10/11 03:14:09 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define TABLE_SIZE 10

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "libft.h"

typedef struct s_proc
{
	pid_t	pid;
	int		status;
	int		ret;
}	t_proc;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_data
{
	char	**envp;
	char	*line;
	char	**path;
	char	*cmd; // variavel dispensavel - não esta sendo usada de verdade. Ver linha 59 do cmd_verification.c
	char	**exec_cmd;
	t_env	**hash_table;
	t_proc	proc;
}	t_data;

void			prompt(t_data *data);
void			exit_program(t_data *data);

void			add_back(t_env **lst, t_env *new);
void			delone(t_env *lst, void (*del)(void*));
t_env			*last_var(t_env *lst);
t_env			*create_var(char	*key, char *value);
void			print_env(t_env *env);

unsigned int	hash(char *name);
char			*get_env_var(t_data *data, char *key);
void			alloc_env_hash(char **envp, t_data *data);
void			print_table(t_env *hash_table[TABLE_SIZE]);

void			set_exec_paths(t_data *data);
void			exec_cmd_son(t_data *data);
void			fork_process(t_data *data);
int				verify_cmd(t_data *data);
void			exec_cmd(t_data *data);
int				wait_and_free(t_data *data);

int				free_and_count_array(char **array, void (*f)(void *));
void			free_hash_table(t_data *data);
void			free_lst(t_env *env);

#endif
