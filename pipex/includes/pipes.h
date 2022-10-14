/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 16:17:20 by vfranco-          #+#    #+#             */
/*   Updated: 2022/10/14 13:12:48 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPES_H
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include "processes.h"
# define PIPES_H

int		open_pipes(t_main *data);
void	close_pipes_until(int **fd, int n);
void	manage_pipes(int **fd, int process_idx, int pipes_qtd);

#endif