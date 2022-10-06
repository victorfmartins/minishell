/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_verifycation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 17:20:26 by asoler            #+#    #+#             */
/*   Updated: 2022/09/28 01:16:29 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_absolute_path(t_data *data)
{
	if (*data->line == '.' || *data->line == '/')
		return (1);
	return (0);
}

void	set_exec_paths(t_data *data)
{
	char	**path_table;
	int		i;

	path_table = ft_split(get_env(data, "PATH"), ':');
	data->path = malloc((table_rows(path_table) + 1) * sizeof(char *));
	i = -1;
	while (path_table[++i])
		data->path[i] = ft_strjoin(path_table[i], "/");
	data->path[i] = NULL;
	free_table(path_table);
}

int	verify_cmd(t_data *data)
{
	char	*join_cmd;
	int		i;

	i = 0;
	data->exec_cmd = ft_split(data->line, ' ');
	if (is_absolute_path(data))
		return (1);
	data->cmd = ft_strdup(data->exec_cmd[0]);
	while (data->path[i])
	{
		join_cmd = ft_strjoin(data->path[i], data->cmd);
		if (!access(join_cmd, F_OK))
		{
			free(data->exec_cmd[0]);
			data->exec_cmd[0] = ft_strdup(join_cmd);
			free(join_cmd);
			return (1);
		}
		free(join_cmd);
		i++;
	}
	return (0);
}
