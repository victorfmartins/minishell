/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 13:00:23 by asoler            #+#    #+#             */
/*   Updated: 2022/11/07 14:24:31 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*heredoc(t_file *lst)
{
	char	*line;
	char	*history_1;
	char	*history_2;
	char	*aux;
	int		fd;
	int		i;

	fd = open(lst->name, O_APPEND | O_CREAT | O_WRONLY, 0644);
	line = readline("> ");
	history_1 = ft_strdup(line); //add_history[last_*char]
	while (ft_strncmp(lst->name, line, ft_strlen(line)))
	{
		aux = ft_strdup(line);
		i = ft_strlen(aux);
		// aux[i] = '\n';
		write(fd, aux, i);
		write(fd, "\n", 1);
		
		//add history
		history_2 = ft_strjoin(history_1, aux);
		free(history_1);
		history_1 = ft_strjoin(history_2, "\n");
		free(history_2);
		// -----
		
		free(aux);
		free(line);
		line = readline("> ");
	}
	//add history
	history_2 = ft_strjoin(history_1, line);
	free(history_1);
	add_history(history_2);
	free(history_2);
	// -----
	write(fd, line, ft_strlen(line));
	free(line);
	close(fd);
	return (lst->name);
}
// [TODO]
// - put file in /tmp/ or something like that
// - make history works
		//*it most record data->line and not repeat firt heredoc line
// - remove file after execution
// - valgrind full checking
