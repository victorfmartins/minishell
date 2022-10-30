/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 16:00:42 by vfranco-          #+#    #+#             */
/*   Updated: 2022/10/30 15:56:41 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	redir_lst_fd_init(t_file *lst, int mode)
{
	if (!lst)
		return ;
	while (lst->next)
	{
		if (lst->type == 1) //O_REDIR
			lst->fd = open(lst->name, O_TRUNC | O_CREAT | O_WRONLY, 0644);
		if (lst->type == 4) // APPEND
			lst->fd = open(lst->name, O_APPEND | O_CREAT | O_WRONLY, 0644);
		else //add HERDOC
			lst->fd = open(lst->name, O_RDONLY);
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

void	close_fds_until(t_data *data)//tratar casos: ex. sem pipe
{
	int		**pipes_fds;
	t_cmd	*node;
	int		n_cmds;
	
	pipes_fds = data->pipex.inter.fd;
	node = data->cmds;
	n_cmds = data->pipex.n_args;
	while (n_cmds >= 0)
	{
		// if (node->infiles->fd != -1)
		// 	close(node->infiles->fd);
		// if (node->outfiles->fd != -1)
		// 	close(node->outfiles->fd);
		close(pipes_fds[n_cmds][0]);
		close(pipes_fds[n_cmds][1]);
		n_cmds--;
	}
	return ;
}

int	init_fds(t_data *data)
{
	// t_inter	*inter;
	int		n_cmds;
	int		i;

	get_files_fds(data->cmds);//here there is just redir
	n_cmds = data->pipex.n_args;
	if (!n_cmds)
		return (0);
	// inter = &data->pipex.inter;
	i = 0;
	while (i < n_cmds)
	{
		if (pipe(data->pipex.inter.fd[i]) == -1) // here there is just pipes
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
	t_cmd	*node;
	t_inter	*pipes_fds;
	int	i;

	node = data->cmds;
	pipes_fds = &data->pipex.inter;
	i = iter;
	while (iter)
	{
		node = node->next;
		iter--;
	}
	if (node->outfiles)
		dup2(node->outfiles->fd, 1);
	else if (node->next)
		dup2(node->infiles->fd, 1);
	if (node->infiles)
		dup2(pipes_fds->fd[i][0], 0);
	else if (node->prev)
		dup2(pipes_fds->fd[i - 1][0], 0);
	close_fds_until(data);
	return ;
}
