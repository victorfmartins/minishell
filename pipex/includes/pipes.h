/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 16:17:20 by vfranco-          #+#    #+#             */
/*   Updated: 2022/10/12 13:12:31 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPES_H
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# define PIPES_H

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

int		open_pipes(t_main *data);
void	close_pipes_until(int **fd, int n);
void	manage_pipes(int **fd, int process_idx, int pipes_qtd);

#endif