/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfranco- <vfranco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 21:09:10 by lufelip2          #+#    #+#             */
/*   Updated: 2022/10/19 15:22:06 by vfranco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	analize_line(t_data *data)
{
	data->cmds = get_file_structures(data);
	print_cmd_lst(data->cmds);
	// exec_cmd(data);
	// free_and_count_array(data->exec_cmd, free);
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
		return ;
	if (!ft_strncmp("exit", data->line, 4))
		exit_program(data);
	analize_line(data);
}
