/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 17:57:10 by vfranco-          #+#    #+#             */
/*   Updated: 2022/10/14 13:08:46 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	pipex(t_main *data)
{
	// 	int	pipe_fd[PIPES][2];
	// int	redir[REDIR]
	// int	id[N_CMD];
	int	i;

	if (open_pipes(data) == -1)
		return (-1);
	i = 0;
	while (i < data->n_args) 
	{
		data->inter.id[i] = fork();
		if (data->inter.id[i] == -1)
		{
			close_pipes_until(data->inter.fd, data->n_args); 
			perror("");
			return (-2);
		}
		if (data->inter.id[i] == 0)
			enter_process_op(data, i);
		i++;
	}
	close_pipes_until(data->inter.fd, data->n_args);
	wait_all_child_finish(data->inter.id, data->n_args, &data->status); //N_ARGS
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	t_main	data;
	int i;

	i = 0;
	data.argc = argc;
	data.n_args = argc - 3;
	data.argv = argv;
	data.envp = envp;
	data.inter.fd = ft_calloc(sizeof(int *), data.n_args);
	data.inter.id = ft_calloc(sizeof(int), data.n_args);
	while (i < data.n_args)
	{
		data.inter.fd[i] = malloc(sizeof(int) * 2);
		i++;
	}
	if (argc < 5)
		return (ft_printf("not enought args\n"));
	if (pipex(&data) == -1)
		return (EXIT_FAILURE);
	free_args(0, 0, &data);
	exit(WEXITSTATUS(data.status));
}
