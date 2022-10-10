/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfranco- <vfranco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 17:57:10 by vfranco-          #+#    #+#             */
/*   Updated: 2022/10/10 14:01:40 by vfranco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	pipex(int argc, char **argv, char **envp, int *status)
{
	int	fd[argc - 3][2];
	int	id[argc - 3];
	int	i;

	if (open_pipes(argc, argv, fd) == -1)
		return (-1);
	i = 0;
	while (i < argc - 3)
	{
		id[i] = fork();
		if (id[i] == -1)
		{
			close_pipes_until(fd, argc - 3);
			perror("");
			return (-2);
		}
		if (id[i] == 0)
			enter_process_op(fd, i, argv, envp, argc - 3);
		i++;
	}
	close_pipes_until(fd, argc - 3);
	wait_all_child_finish(id, argc - 3, status);
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	int	status;

	if (pipex(argc, argv, envp, &status) == -1)
		return (EXIT_FAILURE);
	exit(WEXITSTATUS(status));
}
