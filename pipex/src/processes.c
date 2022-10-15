/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 16:01:50 by vfranco-          #+#    #+#             */
/*   Updated: 2022/10/15 20:50:33 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	free_args(char ***args, char **cmd, t_main *data)
{
	int	i;

	i = 0;
	if (args && cmd)
	{
		while ((*args)[i])
			free((*args)[i++]);
		free(*args);
		free(*cmd);
	}
	i = 0;
	while (i < data->n_args)
	{
		free(data->inter.fd[i]);
		i++;
	}
	free(data->inter.fd);
	free(data->inter.id);
}

int	enter_process_op(t_main *data, int process_idx)
{
	char	**args;
	char	*cmd;

	manage_pipes(data, process_idx);
	args = ft_split_pass(data->argv[process_idx + 2], ' ', '\''); //parsing cmds and its args
	cmd = ft_strjoin("/usr/bin/", args[0]); //reemplazar por verify_cmd
	execve(cmd, args, data->envp);
	exit(process_error(&args, &cmd, data));
	return (1);
}

int	process_error(char ***args, char **cmd, t_main *data)
{
	if (access(*cmd, F_OK) == -1 || !(*args)[0])
	{
		write(2, "pipex: ", 7);
		if ((*args)[0])
			ft_putstr_fd((*args)[0], 2);
		write(2, ": command not found\n", 20);
		free_args(args, cmd, data);
		return (127);
	}
	perror("pipex"); //"error" ou strerror(perror);
	free_args(args, cmd, data);
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
