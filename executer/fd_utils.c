/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 16:00:42 by vfranco-          #+#    #+#             */
/*   Updated: 2022/11/07 12:52:49 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	redir_lst_fd_init(t_file *lst, int mode)
{
	if (!lst)
		return ;
	while (lst)
	{
		if (lst->type == O_REDIR)
			lst->fd = open(lst->name, O_TRUNC | O_CREAT | O_WRONLY, 0644);
		else if (lst->type == APPEND)
			lst->fd = open(lst->name, O_APPEND | O_CREAT | O_WRONLY, 0644);
		else
			lst->fd = open(lst->name, O_RDONLY);
		verify_access(lst->name, mode);
		if (lst->next)
			lst = lst->next;
		else
			break ;
	}
}

static int	get_files_fds(t_cmd *node)
{
	while (node)
	{
		if (node->infiles)
			redir_lst_fd_init(node->infiles, W_OK);
		if (node->outfiles)
			redir_lst_fd_init(node->outfiles, R_OK);
		if (node->next)
			node = node->next;
		else
			break ;
	}
	return (1);
}

void	close_file_fds(t_cmd *node)
{
	while (node)
	{
		if (node->infiles)
			close(node->infiles->fd);
		if (node->outfiles)
			close(node->outfiles->fd);
		if (node->next)
			node = node->next;
		else
			break ;
	}
}

void	close_fds(t_data *data)
{
	int		**pipes_fds;
	int		n_cmds;

	n_cmds = data->exec.n_args;
	if (data->exec.inter.fd)
		pipes_fds = data->exec.inter.fd;
	while (n_cmds > 0)
	{
		n_cmds--;
		close(pipes_fds[n_cmds][0]);
		close(pipes_fds[n_cmds][1]);
	}
	close_file_fds(data->cmds);
	return ;
}

int	init_fds(t_data *data)
{
	t_inter	*inter;
	int		n_cmds;
	int		i;

	get_files_fds(data->cmds);
	n_cmds = data->exec.n_args;
	if (!n_cmds)
		return (0);
	inter = &data->exec.inter;
	i = 0;
	while (i < n_cmds)
	{
		if (pipe(inter->fd[i]) == -1)
		{
			perror("something went wrong with pipe function");
			return (-1);
		}
		i++;
	}
	return (0);
}
