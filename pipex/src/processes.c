/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 16:01:50 by vfranco-          #+#    #+#             */
/*   Updated: 2022/10/12 13:10:39 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/processes.h"

static void	free_args(char ***args, char **cmd)
{
	int	i;

	i = 0;
	while ((*args)[i])
		free((*args)[i++]);
	free(*args);
	free(*cmd);
}

int	enter_process_op(t_main *data, int process_idx)
{
	char	**args;
	char	*cmd;

	manage_pipes(data->inter.fd, process_idx, data->n_args);
	args = ft_split_pass(data->argv[process_idx + 2], ' ', '\''); //parsing cmds and its args
	cmd = ft_strjoin("/usr/bin/", args[0]); //reemplazar por verify_cmd
	execve(cmd, args, data->envp);
	exit(process_error(&args, &cmd));
	return (1);
}

int	process_error(char ***args, char **cmd)
{
	if (!(*args)[0])
	{
		write(2, "pipex: ", 7);
		ft_putstr_fd("", 2);
		write(2, ": command not found\n", 20);
		free_args(args, cmd);
		return (127);
	}
	else if (access(*cmd, F_OK) == -1)
	{
		write(2, "pipex: ", 7);
		ft_putstr_fd((*args)[0], 2);
		write(2, ": command not found\n", 20);
		free_args(args, cmd);
		return (127);
	}
	else
		perror("pipex"); //"error" ou strerror(perror);
	free_args(args, cmd);
	return (1);
}

void	wait_all_child_finish(int id[], int child_qtd, int *status)
{
	int	i;

	i = 0;
	while (i < child_qtd)
	{
		waitpid(id[i], status, 0);
		i++;
	}
}
