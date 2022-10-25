/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 16:00:42 by vfranco-          #+#    #+#             */
/*   Updated: 2022/10/25 15:26:45 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	redir_lst_fd_init(t_file *lst, int mode)
{
	while (lst->next)
	{
		if (lst->type = 1) //O_REDIR
			lst->fd = open(name, O_TRUNC | O_CREAT | O_WRONLY, 0644);
		if (lst->type = 4) // APPEND
			lst->fd = open(name, O_APPEND | O_CREAT | O_WRONLY, 0644);
		else //add HERDOC
			lst->fd = open(name, O_RDONLY);
		verify_access(lst->name, mode);
		lst = lst->next;
	}
}

static int	get_files_fds(t_cmd *node)//recebe struct q conteim path, mode, e fd que sera alocado
{
	while (node->next)
	{
		redir_lst_fd_init(node->infiles, W_OK);
		redir_lst_fd_init(node->outfiles,  R_OK);
		node = node->next;
	}
	return (1);
}

void	close_fds_until(int **fd, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		if (fd[i][0] >= 0)
			close(fd[i][0]);
		if (fd[i][1] >= 0)
			close(fd[i][1]);
		i++;
	}
	return ;
}

int	init_fds(t_data *data)
{
	t_inter	*inter;
	int		n_cmds;

	get_files_fds(data->cmds);//here there is just redir
	n_cmds = data->pipex->n_args;
	inter = data->pipex->inter;
	while (i < n_cmds)
	{
		if (pipe(inter->fd[i]) == -1) // here there is just pipes
		{
			// close_fds_until(inter->fd, i);
			perror("something went wrong with pipe function");
			return (-1);
		}
		i++;
	}
	return (0);
}

void	dup_fds(t_data *data, int iter)//dup_fds*** or manage_dup
{
	int	i;

	i = 0;
	// se os fds de infile e outfile retornam -1 não se faz dup
	if ((iter == 0 && data->inter.fd[0][0] == -1) || (iter == (data->n_args - 1) && data->inter.fd[0][1] == -1))
	{
		free_args(0, 0, data);
		exit(1);
	}
	dup2(data->inter.fd[iter][0], STDIN_FILENO);
	if (iter != (data->n_args - 1))
		dup2(data->inter.fd[iter + 1][1], STDOUT_FILENO);
	else
		dup2(data->inter.fd[0][1], STDOUT_FILENO);
	close_fds_until(data->inter.fd, data->n_args);
	return ;
}
