/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 18:04:09 by vfranco-          #+#    #+#             */
/*   Updated: 2022/10/30 15:37:09 by asoler           ###   ########.fr       */
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
# define PIPEX_H

// typedef struct s_inter
// {
// 	int	**fd; 
// 	int	*id;
// }	t_inter;

// typedef struct s_main
// {
// 	char	**argv;
// 	char	**envp;
// 	int		argc;
// 	int		n_args;
// 	int		status;
// 	t_inter	inter;
// }	t_main;

int		verify_access(char *path, int mode);

// int		enter_process_op(t_data *data, int fds_idx);
// // void	free_args(char ***args, char **cmd, t_main *data); //free fds
// void	wait_all_child_finish(int id[], t_data *data);

// int		init_fds(t_data *data);
// void	close_fds_until(t_data *data);
// void	dup_fds(t_data *data, int iter);

#endif