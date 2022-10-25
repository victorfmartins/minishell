/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cmd_attributes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfranco- <vfranco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 20:36:35 by vfranco-          #+#    #+#             */
/*   Updated: 2022/10/24 18:35:19 by vfranco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	get_cmd_type(char *line)
{
	char	*trimed_line;

	trimed_line = ft_strtrim(line, " \f\n\r\t\v");
	if ((ft_strncmp(trimed_line, "echo", 4) == 0)
		|| (ft_strncmp(trimed_line, "cd", 2) == 0)
		|| (ft_strncmp(trimed_line, "pwd", 3) == 0)
		|| (ft_strncmp(trimed_line, "export", 6) == 0)
		|| (ft_strncmp(trimed_line, "unset", 5) == 0)
		|| (ft_strncmp(trimed_line, "env", 3) == 0)
		|| (ft_strncmp(trimed_line, "exit", 4) == 0))
	{
		free(trimed_line);
		return (BUILTIN);
	}
	free(trimed_line);
	return (0);
}

int	get_cmd_attributes(t_cmd **cmd)
{
	(*cmd)->args = ft_split_but_through_quotes((*cmd)->line, ' ');
	(*cmd)->type = get_cmd_type((*cmd)->args[0]);
	(*cmd)->exec_cmd = ft_strjoin("/usr/bin/", (*cmd)->args[0]);
	return (0);
}
