/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 22:57:04 by asoler            #+#    #+#             */
/*   Updated: 2022/11/23 12:43:43 by vfranco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"
# include "parser.h"
# include "executer.h"
# include "environment.h"
# define MINISHELL_H

# define I_REDIR 1
# define HERE_DOC 2
# define O_REDIR 3
# define APPEND 4
# define BUILTIN 6
# define ABSPATH 7

typedef struct s_data
{
	char	**envp;
	char	*line;
	char	**path;
	t_main	exec;
	t_cmd	*cmds;
	t_env	**hash_table;
}	t_data;

void	prompt(t_data *data);
void	exit_program(t_data *data);

t_cmd	*get_file_structures(t_data *data);

char	*get_env_var(t_data *data, char *key);
void	alloc_env_hash(char **envp, t_data *data);
void	set_exec_paths(t_data *data);
void	free_hash_table(t_data *data);

int		executer(t_data *data);
int		ft_exec(t_data *data, t_cmd *node);
int		verify_cmd(char **path, t_cmd *node);
int		wait_and_free( t_data *data);

int		init_fds(t_data *data);
void	close_fds(t_data *data);

char	*heredoc(t_file *lst);

void	expansions(t_data data, t_cmd **cmds);
void	tilde_expansion(t_data data, char **s);
void	env_var_expansion(t_data data, char **s);
char	*ft_strsubstitute(char *str, char *del, char *insert, int pos);
char	*ft_strcpy_until(char *str, char *delimiter);

#endif
