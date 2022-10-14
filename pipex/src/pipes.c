/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 16:00:42 by vfranco-          #+#    #+#             */
/*   Updated: 2022/10/14 13:29:57 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipes.h"

static int	get_files_fds(t_main *data)
{
	data->inter.fd[0][0] = open(data->argv[1], O_RDONLY);
	data->inter.fd[0][1] = open(data->argv[data->argc - 1], O_TRUNC | O_CREAT | O_WRONLY, 0644);
	if (data->inter.fd[0][1] == -1 || data->inter.fd[0][0] == -1)
	{
		if (data->inter.fd[0][0] == -1)
			perror(data->argv[1]);
		else if (data->inter.fd[0][1] == -1)
			perror(data->argv[data->argc - 1]);
	}
	return (1);
}

void	close_pipes_until(int **fd, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		close(fd[i][0]);
		close(fd[i][1]);
		i++;
	}
	return ;
}

int	open_pipes(t_main *data)
{
	int	i;

	get_files_fds(data);//here there is just redir
	i = 1;
	while (i < data->n_args)
	{
		if (pipe(data->inter.fd[i]) == -1) // here there is just pipes
		{
			close_pipes_until(data->inter.fd, i);
			perror("");
			return (-1);
		}
		i++;
	}
	return (0);
}

void	manage_pipes(int **fd, int process, int pipes_qtd)//dup_fds*** or manage_dup
{
	int	i;

	i = 0;
	if ((process == 0 && fd[0][0] == -1) || (process == 1 && fd[0][1] == -1))
		exit(1);
	while (i < pipes_qtd)
	{
		if ((process != 0 && i == process) || (process == 0 && i == 0))
			dup2(fd[i][0], STDIN_FILENO);
		if (i == process + 1 || (process == pipes_qtd - 1 && i == 0))
			dup2(fd[i][1], STDOUT_FILENO);
		i++;
	}
	close_pipes_until(fd, pipes_qtd);
	return ;
}
