/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 18:04:09 by vfranco-          #+#    #+#             */
/*   Updated: 2022/10/23 16:38:35 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include "../../includes/libft.h"
# include "../../includes/minishell.h"
# define PIPEX_H
# define PIPE 1
# define INREDIR 2
# define OUTREDIR 3
# define APPEND 4
# define HEREDOC 5

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
	t_inter	inter;
}	t_main;

typedef struct s_file
{
	char	*name;
	int		mode;
	int		fd;
} t_file;

typedef struct s_cmd
{
	char	*cmd;
	char	**args;
	t_file	*in;
	t_file	*out;
} t_cmd;

int		verify_access(char *path, int mode);

void	free_args(char ***args, char **cmd, t_main *data);
int		enter_process_op(t_main *data, int fds_idx);
void	wait_all_child_finish(int id[], int child_qtd, int *status);

int		open_fds(t_main *data);
void	close_fds_until(int **fd, int n);
void	manage_fds(t_main *data, int iter);

char	**ft_split_pass(char const *s, char c, char l);

size_t	count_words(char *str, char c, char l);
size_t	word_lenght(char *str, char c, char l);
void	free_until(char **arr, int n);

#endif