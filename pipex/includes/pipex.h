/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 18:04:09 by vfranco-          #+#    #+#             */
/*   Updated: 2022/10/12 13:12:19 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# include "pipes.h"
# include "processes.h"
# include "split_pass.h"
# include "split_utils.h"
# include "../../includes/libft.h"
# define PIPEX_H
# define PIPES 1
# define REDIR 2
# define N_CMD 2
# define N_ARGS PIPES + (REDIR / 2)

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


#endif