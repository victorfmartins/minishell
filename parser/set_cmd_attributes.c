/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cmd_attributes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 20:36:35 by vfranco-          #+#    #+#             */
/*   Updated: 2022/11/26 16:28:11 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	get_cmd_type(char *line)
{
	char	*trimed_line;
	int		type;

	trimed_line = ft_strtrim(line, " \f\n\r\t\v");
	if (!trimed_line)
		return (0);
	type = is_absolute_path(trimed_line);
	if ((ft_strncmp(trimed_line, "echo", 4) == 0)
		|| (ft_strncmp(trimed_line, "cd", 2) == 0)
		|| (ft_strncmp(trimed_line, "pwd", 3) == 0)
		|| (ft_strncmp(trimed_line, "export", 6) == 0)
		|| (ft_strncmp(trimed_line, "unset", 5) == 0)
		|| (ft_strncmp(trimed_line, "env", 3) == 0)
		|| (ft_strncmp(trimed_line, "exit", 4) == 0))
		type = BUILTIN;
	if (type == -1)
		type = 0;
	free(trimed_line);
	return (type);
}

void	get_cmd_attributes(t_cmd **cmd)
{
	(*cmd)->args = ft_split_but_through_quotes((*cmd)->line, ' ');
	if (*(*cmd)->args)
	{
		(*cmd)->type = get_cmd_type((*cmd)->args[0]);
		(*cmd)->exec_cmd = ft_strdup((*cmd)->args[0]);
	}
	else
	{
		(*cmd)->type = 0;
		(*cmd)->exec_cmd = NULL;
	}
}
