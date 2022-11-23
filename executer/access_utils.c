/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfranco- <vfranco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 21:21:37 by asoler            #+#    #+#             */
/*   Updated: 2022/11/23 15:02:21 by vfranco-         ###   ########.fr       */
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

static int	is_absolute_path(char *arg)
{
	if (*arg == '/')
	{
		if (verify_access(arg, F_OK))
			return (1);
		else
		{
			write(2, "bash: ", 6);
			ft_putstr_fd(arg, 2);
			write(2, ": No such file or directory\n", 28);
			return (-1);
		}
	}
	return (0);
}

void	print_cmd_error(char *arg)
{
	write(2, "bash: ", 6);
	ft_putstr_fd(arg, 2);
	write(2, ": command not found\n", 20);
}

int	verify_cmd(char **path, t_cmd *node)
{
	char	*join_cmd;
	int		i;

	if (!node->exec_cmd)
		return (0);
	i = is_absolute_path(node->args[0]);
	if (i == 1)
		return (1);
	if (i == -1)
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
	print_cmd_error(node->args[0]);
	return (0);
}
