/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfranco- <vfranco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 16:17:20 by vfranco-          #+#    #+#             */
/*   Updated: 2022/10/07 16:58:46 by vfranco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPES_H
# define PIPES_H

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>

void	close_pipes_until(int fd[][2], int n);
int		open_pipes(int argc, char **argv, int fd[][2]);
void	manage_pipes(int fd[][2], int process_idx, int pipes_qtd);

#endif