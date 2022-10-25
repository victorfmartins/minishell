/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 16:00:42 by vfranco-          #+#    #+#             */
/*   Updated: 2022/10/24 13:53:03 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static int	get_files_fds(t_main *data)//recebe struct q conteim path, mode, e fd que sera alocado
{
	char	*infile;
	char	*outfile;

	infile = data->argv[1];
	outfile = data->argv[data->argc - 1];
	data->inter.fd[0][0] = open(infile, O_RDONLY);
	data->inter.fd[0][1] = open(outfile, O_TRUNC | O_CREAT | O_WRONLY, 0644);
	// data->inter.fd[0][1] = open(outfile, O_APPEND | O_WRONLY);
	verify_access(infile, R_OK);
	verify_access(outfile, W_OK);
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

int	open_fds(t_main *data)
{
	int	i;

	get_files_fds(data);//here there is just redir
	i = 1;
	while (i < data->n_args)
	{
		if (pipe(data->inter.fd[i]) == -1) // here there is just pipes
		{
			close_fds_until(data->inter.fd, i);
			perror("");
			return (-1);
		}
		i++;
	}
	return (0);
}

void	manage_fds(t_main *data, int iter)//dup_fds*** or manage_dup
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
