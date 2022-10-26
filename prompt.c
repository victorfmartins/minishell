/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 21:09:10 by lufelip2          #+#    #+#             */
/*   Updated: 2022/10/26 15:19:55 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	analize_line(t_data *data)
{
	data->cmds = get_file_structures(data);
	// print_cmd_lst(data->cmds);
	pipex(data);
	ft_cmdclear(&data->cmds, free);
	free(data->line);
}

void	prompt(t_data *data)
{
	char	*path;

	path = getcwd(0, 0);
	printf("%s\n", path);
	free(path);
	data->line = readline("❯ ");
	if (*data->line)
		add_history(data->line);
	else
	{
		free(data->line);
		return ;
	}
	if (!ft_strncmp("exit", data->line, 4))
		exit_program(data);
	analize_line(data);
}
