/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfranco- <vfranco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 22:57:04 by asoler            #+#    #+#             */
/*   Updated: 2022/10/08 11:52:24 by vfranco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#define TABLE_SIZE 10

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
	char	*line;
	t_env	*hash_table[TABLE_SIZE];
	char	**path;
	char	*cmd;
	char	**exec_cmd;
	t_proc	proc;
}	t_data;

void	prompt(t_data *data);
void	print_env(t_env *env);
void	free_table(char **table);
void	add_back(t_env **lst, t_env *new);
void	delone(t_env *lst, void (*del)(void*));
t_env	*last_var(t_env *lst);
t_env	*create_var(char	*key, char *value);
void	alloc_env(char **envp, t_env **env);
char	*get_env(t_data *data, char *env);
int		table_rows(char **table);

void	set_exec_paths(t_data *data);
void	exec_cmd_son(t_data *data);
void	fork_process(t_data *data);
int		verify_cmd(t_data *data);
void	exec_cmd(t_data *data);
int		wait_and_free(t_data *data);

#endif
