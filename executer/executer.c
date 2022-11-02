/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 17:57:10 by vfranco-          #+#    #+#             */
/*   Updated: 2022/11/02 10:12:36 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_procs(t_cmd *head)
{
	int		n;

	n = 0;
	while(head->next)
	{
		if (head->exec_cmd && head->next->exec_cmd)
			n++;
		head = head->next;
	}
	return (n);
}

int	init_proc_data(t_data *data)
{
	// t_main	*main;
	// main = &data->pipex;
	int		i;

	i = 0;
	if (data->pipex.n_args > 0) //desenvolver condições de verificações t_cmd lst
	{
		data->pipex.inter.fd = ft_calloc(sizeof(int *), data->pipex.n_args);
		data->pipex.inter.id = ft_calloc(sizeof(int), data->pipex.n_args + 1);
		while (i < data->pipex.n_args)
		{
			data->pipex.inter.fd[i] = malloc(sizeof(int) * 2);
			i++;
		}
	}
	else
	{
		data->pipex.inter.fd = NULL;
		data->pipex.inter.id = ft_calloc(sizeof(int), 1);
	}
	return (init_fds(data));
}

int	executer(t_data *data)
{
	int		i;
	t_cmd	*node;

	data->pipex.n_args = count_procs(data->cmds); //n_args = n_pipes count_pipes
	node = data->cmds;
	if (init_proc_data(data) < 0)// alloc fds de aquivos e pipes
		return (-1);
	i = 0;
	while (node)
	{
		node->index = i;// em caso de fazer o wait sincrono
		if (verify_cmd(data->path, node))
		{
			data->pipex.inter.id[i] = fork();
			if (data->pipex.inter.id[i] == 0)
				enter_process_op(data, node);
		}
		if (!node->next)
			break;
		else
			node = node->next;
		i++;
	}
	close_fds(data);
	wait_and_free(data);
	return (1);
}

