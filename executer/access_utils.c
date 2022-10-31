/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 21:21:37 by asoler            #+#    #+#             */
/*   Updated: 2022/10/31 03:32:41 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	verify_access(char *path, int mode)
{
	if (access(path, mode) < 0)
	{
		if (mode == R_OK || mode == W_OK)
			ft_printf("bash: %s: %s\n", path, strerror(errno));
		return (0);
	}
	return (1);
}

int	verify_cmd(char **path, t_cmd *node)
{
	char	*join_cmd;
	int		i;

	if (!node->exec_cmd) //proteção para node que não é de comando
		return (0);
	i = 0;
	while (path[i])
	{
		join_cmd = ft_strjoin(path[i], node->args[0]);
		if (verify_access(join_cmd, F_OK))
		{
			free(node->exec_cmd);
			node->exec_cmd = join_cmd;
			return (1);
		}
		free(join_cmd);
		i++;
	}
	write(2, "bash: ", 6);
	ft_putstr_fd(node->args[0], 2);
	write(2, ": command not found\n", 20);
	return (0);
}
