/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 21:21:37 by asoler            #+#    #+#             */
/*   Updated: 2022/10/30 15:49:58 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

int	verify_cmd(t_data *data)
{
	char	*join_cmd;
	int		i;

	i = 0;
	while (data->path[i])
	{
		join_cmd = ft_strjoin(data->path[i], data->cmds->args[0]);
		if (verify_access(join_cmd, F_OK))
		{
			free(data->cmds->exec_cmd);
			data->cmds->exec_cmd = ft_strdup(join_cmd);
			free(join_cmd);
			return (1);
		}
		free(join_cmd);
		i++;
	}
	write(2, "bash: ", 6);
	ft_putstr_fd(data->cmds->args[0], 2);
	write(2, ": command not found\n", 20);
	return (0);
}
