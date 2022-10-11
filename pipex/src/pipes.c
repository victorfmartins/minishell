/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 16:00:42 by vfranco-          #+#    #+#             */
/*   Updated: 2022/10/11 03:57:09 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipes.h"

static int	get_files_fds(int argc, char **argv, int fd[][2])
{
	fd[0][0] = open(argv[1], O_RDONLY);
	if (fd[0][0] == -1)
		perror(argv[1]);
	fd[0][1] = open(argv[argc - 1], O_TRUNC | O_CREAT | O_WRONLY, 0644);
	if (fd[0][1] == -1)
		perror(argv[argc - 1]);
	return (1);
}

void	close_pipes_until(int fd[][2], int n)
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

int	open_pipes(int argc, char **argv, int fd[][2])
{
	int	i;

	get_files_fds(argc, argv, fd);
	i = 1;
	while (i < argc - 3)
	{
		if (pipe(fd[i]) == -1) // return the fd[i][0] (read) and fd[i][1] (write)
		{
			close_pipes_until(fd, i);
			perror("");
			return (-1);
		}
		i++;
	}
	return (0);
}

void	manage_pipes(int fd[][2], int process, int pipes_qtd)//dup_fds*** or manage_dup
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
