/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 17:57:10 by vfranco-          #+#    #+#             */
/*   Updated: 2022/11/02 18:24:47 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_pipes(t_cmd *head)
{
	int		n;

	n = 0;
	while (head->next)
	{
		if (head->exec_cmd && head->next->exec_cmd)
			n++;
		head = head->next;
	}
	return (n);
}

int	init_proc_data(t_data *data)
{
	t_main	*main;
	int		i;

	i = 0;
	main = &data->pipex;
	if (main->n_args > 0)
	{
		main->inter.fd = ft_calloc(sizeof(int *), main->n_args);
		main->inter.id = ft_calloc(sizeof(int), main->n_args + 1);
		while (i < main->n_args)
		{
			main->inter.fd[i] = malloc(sizeof(int) * 2);
			i++;
		}
	}
	else
	{
		main->inter.fd = NULL;
		main->inter.id = ft_calloc(sizeof(int), 1);
	}
	return (init_fds(data));
}

int	get_pid(t_data *data, t_cmd *node)
{
	int	i;

	i = node->index;
	if (verify_cmd(data->path, node))
	{
		data->pipex.inter.id[i] = fork();
		if (data->pipex.inter.id[i] == 0)
			ft_exec(data, node);
		return (1);
	}
	return (0);
}

int	executer(t_data *data)
{
	int		i;
	t_cmd	*node;

	data->pipex.n_args = count_pipes(data->cmds);
	node = data->cmds;
	init_proc_data(data);
	i = 0;
	while (node)
	{
		node->index = i;
		if (!get_pid(data, node))
			data->pipex.inter.id[i] = -1;
		if (!node->next)
			break ;
		else
			node = node->next;
		i++;
	}
	close_fds(data);
	wait_and_free(data);
	return (1);
}
