/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 16:01:50 by vfranco-          #+#    #+#             */
/*   Updated: 2022/11/02 18:24:48 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	dup_fds(t_data *data, t_cmd *node)
{
	t_inter	*pipes_fds;
	int		i;

	pipes_fds = &data->pipex.inter;
	i = node->index;
	if (node->infiles)
		dup2(node->infiles->fd, 0);
	else if (node->prev)
		dup2(pipes_fds->fd[i - 1][0], 0);
	if (node->outfiles)
		dup2(node->outfiles->fd, 1);
	else if (node->next)
		dup2(pipes_fds->fd[i][1], 1);
	return ;
}

int	ft_exec(t_data *data, t_cmd *node)
{
	dup_fds(data, node);
	close_fds(data);
	execve(node->exec_cmd, node->args, data->envp);
	perror("Execve fail");
	return (1);
}

void	free_fds(t_data *data, int n_cmds)
{
	free(data->pipex.inter.id);
	while (n_cmds > 0)
	{
		n_cmds--;
		free(data->pipex.inter.fd[n_cmds]);
	}
	free(data->pipex.inter.fd);
}

int	wait_and_free(t_data *data)
{
	int	status;
	int	ret;
	int	n_cmds;
	int	i;

	n_cmds = data->pipex.n_args;
	ret = 0;
	i = 0;
	status = -1;
	while (i <= n_cmds)
	{
		if (data->pipex.inter.id[i] != -1)
		{
			if (waitpid(data->pipex.inter.id[i], &status, 0) < 0)
				ft_printf("Wait fail: %s\n", strerror(errno));
		}
		i++;
	}
	free_fds(data, n_cmds);
	if (status < 0)
		return (127);
	if (WIFEXITED(status))
		ret = WEXITSTATUS(status);
	return (ret);
}