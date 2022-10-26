/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 17:57:10 by vfranco-          #+#    #+#             */
/*   Updated: 2022/10/26 15:15:03 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_procs(void *head)
{
	int		n;

	n = 0;
	while(head->next)
	{
		head = head->next;
		if (head->exec_cmd)
			n++;
	}
	return (n);
}

int	init_data(t_data *data)
{
	t_main	*main;

	main = &data->pipex;
	main->n_args = count_procs;
	main->envp = data->envp;
	main->inter.fd = ft_calloc(sizeof(int *), main->n_args);
	main->inter.id = ft_calloc(sizeof(int), main->n_args);
	while (i < data.n_args)
	{
		data.inter.fd[i] = malloc(sizeof(int) * 2);
		i++;
	}
	init_fds(data);
}

int	pipex(t_data *data)
{
	int	i;

	if (init_data(data) == -1)// alloc fds de aquivos e pipes
		return (-1);
	i = 0;
	while (i < data->n_args)//n_args => quantidade de cmds e forks que serão executado
	{
		data->inter.id[i] = fork();
		if (data->inter.id[i] == -1)
		{
			// close_fds_until(data->inter.fd, data->n_args);
			perror("somenthing went wrong with fork function");
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

