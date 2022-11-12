/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 13:00:23 by asoler            #+#    #+#             */
/*   Updated: 2022/11/12 16:22:42 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	treat_empty_line(int fd)
{
	char	*endl;

	endl = calloc(sizeof(char), 2);
	endl[0] = '\n';
	ft_putstr_fd(endl, fd);
	free(endl);
}

void	heredoc_readline(char *file_name, int fd)
{
	char	*line;

	line = NULL;
	while (1)
	{
		if (line)
			free(line);
		line = readline("> ");
		if (!*line)
		{
			treat_empty_line(fd);
			continue ;
		}
		if (!ft_strncmp(file_name, line, ft_strlen(line)))
			break ;
		ft_putendl_fd(line, fd);
	}
	free(line);
}

char	*heredoc(t_file *lst)
{
	int		fd;

	fd = open(lst->name, O_APPEND | O_CREAT | O_WRONLY, 0644);
	heredoc_readline(lst->name, fd);
	close(fd);
	return (lst->name);
}
// [TODO]
// - make ft that creates a not existing file
// - put file in /tmp/ or something like that
// - remove file after execution
// - valgrind full checking
