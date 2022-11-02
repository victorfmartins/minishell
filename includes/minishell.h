/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 22:57:04 by asoler            #+#    #+#             */
/*   Updated: 2022/11/02 10:12:22 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "libft.h"
# define MINISHELL_H

# define TABLE_SIZE 10


# define I_REDIR 1
# define HERE_DOC 2
# define O_REDIR 3
# define APPEND 4
# define BUILTIN 6

typedef struct s_inter
{
	int	**fd; 
	int	*id;
}	t_inter;

typedef struct s_main
{
	char	**argv;
	char	**envp;
	int		argc;
	int		n_args;
	int		status;
	int		ret;
	t_inter	inter;
}	t_main;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_file
{
	char			*name;
	int				type;
	int				fd;
	struct s_file	*next;
}	t_file;

typedef struct s_cmd
{
	char			*line;
	char			*exec_cmd;
	char			**args;
	int				type;
	int				index;
	t_file			*infiles;
	t_file			*outfiles;
	struct s_cmd	*prev;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_data
{
	char	**envp;
	char	*line;
	char	**path;
	t_main	pipex;
	t_cmd	*cmds;
	t_env	**hash_table;
}	t_data;

int				executer(t_data *data);
int				verify_cmd(char **path, t_cmd *node);
int				verify_access(char *path, int mode);
int				enter_process_op(t_data *data, t_cmd *node);
int				wait_and_free( t_data *data);

void			dup_fds(t_data *data, t_cmd *node);
int				init_fds(t_data *data);
void			close_fds(t_data *data);

void			prompt(t_data *data);
void			exit_program(t_data *data);

t_env			*ft_envnew(char	*key, char *value);
void			ft_env_addback(t_env **lst, t_env *new);
void			ft_envdelone(t_env *env, void (*del)(void*));
void			ft_envclear(t_env **env, void (*del)(void *));
void			print_env_lst(t_env *env);
void			set_exec_paths(t_data *data);

unsigned int	hash(char *name);
char			*get_env_var(t_data *data, char *key);
void			alloc_env_hash(char **envp, t_data *data);
void			print_table(t_env *hash_table[TABLE_SIZE]);

int				free_and_count_array(char **array, void (*f)(void *));
void			free_hash_table(t_data *data);
void			free_lst(t_env *env);

// void			print_lst(t_list *lst);
t_cmd			*get_file_structures(t_data *data);
t_cmd			*ft_split_to_cmd_lst(char *line, char delimiter);
size_t			ft_new_line_size(char *str, int mode);
void			get_cmd_attributes(t_cmd **cmd);

t_file			*ft_filenew(char *name, int type);
t_cmd			*ft_cmdnew(char *phrase);
void			ft_file_addback(t_file **lst, t_file *new);
void			ft_cmd_addback(t_cmd **lst, t_cmd *new);
void			ft_filedelone(t_file *file, void (*del)(void *));
void			ft_fileclear(t_file **file, void (*del)(void *));
void			ft_cmddelone(t_cmd *cmd, void (*del)(void *));
void			ft_cmdclear(t_cmd **lst, void (*del)(void *));
void			ft_clear_array(char **array);
void			print_file_lst(t_file *lst);
void			print_cmd_lst(t_cmd *lst);
void			print_array_args(char **args);

char			*ft_worddup(char *s1, const char *delimiters);
void			copy_through_quotes(char *s, char **new_s, int *i, int *j);
void			pass_through_quotes(char *str, size_t *i, size_t *size);
char			**ft_split_but_through_quotes(char const *s, char delimiter);

int				pipex(t_data *data);

#endif
