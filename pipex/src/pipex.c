/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 17:57:10 by vfranco-          #+#    #+#             */
/*   Updated: 2022/10/16 01:52:15 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	pipex(t_main *data)
{
	int	i;

	if (open_fds(data) == -1)// alloc fds de aquivos e pipes arquivos e pipes
		return (-1);
	i = 0;
	while (i < data->n_args)//n_args => quantidade de cmds e froks que serão executado
	{
		data->inter.id[i] = fork();
		if (data->inter.id[i] == -1)
		{
			close_fds_until(data->inter.fd, data->n_args); 
			perror("");
			return (-2);
		}
		if (data->inter.id[i] == 0)
			enter_process_op(data, i);
		i++;
	}
	close_fds_until(data->inter.fd, data->n_args);
	wait_all_child_finish(data->inter.id, data->n_args, &data->status);
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
	{
		free_args(0, 0, &data);
		return (EXIT_FAILURE);
	}
	free_args(0, 0, &data);
	exit(WEXITSTATUS(data.status));
}
