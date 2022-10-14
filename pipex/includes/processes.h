/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 16:25:37 by vfranco-          #+#    #+#             */
/*   Updated: 2022/10/14 13:12:59 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROCESSES_H
# define PROCESSES_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/wait.h>

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

 void	free_args(char ***args, char **cmd, t_main *data);
int		enter_process_op(t_main *data, int process_idx);
int		process_error(char ***args, char **cmd, t_main *data);
void	wait_all_child_finish(int id[], int child_qtd, int *status);

#endif