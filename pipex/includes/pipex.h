/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 18:04:09 by vfranco-          #+#    #+#             */
/*   Updated: 2022/10/16 01:46:10 by asoler           ###   ########.fr       */
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
# define PIPES 1
# define REDIR 2
# define N_CMD 2


typedef struct s_inter
{
	// t_proc	*cmd;
	// t_files	*files;
	int	**fd; //os fds de io_files estao em [0] o pipe em [1]-> that means that [0] cloud be used dinamic alloc so it had the redir fd only?
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

// typedef struct s_pipes
// {
// 	int	pipes_fds[PIPES][2];
// }	t_pipes;

// typedef struct s_proc
// {
// 	int	io_fds[2];//**
// 	int	*id;
// 	t_pipes	pipe;//**
// }	t_proc;

// typedef struct s_files
// {
// 	t_redir	redir[REDIR];
// 	int	type;
// }	t_files;

// typedef struct s_redir
// {
// 	char	*file;
// 	int		fd;
// 	int		type;
// }	t_redir;

int		verify_access(char *path, int mode);

void	free_args(char ***args, char **cmd, t_main *data);
int		enter_process_op(t_main *data, int process_idx);
void	wait_all_child_finish(int id[], int child_qtd, int *status);

int		open_fds(t_main *data);
void	close_fds_until(int **fd, int n);
void	manage_fds(t_main *data, int process_idx);

char	**ft_split_pass(char const *s, char c, char l);

size_t	count_words(char *str, char c, char l);
size_t	word_lenght(char *str, char c, char l);
void	free_until(char **arr, int n);

#endif