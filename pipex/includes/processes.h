/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfranco- <vfranco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 16:25:37 by vfranco-          #+#    #+#             */
/*   Updated: 2022/10/10 13:19:55 by vfranco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROCESSES_H
# define PROCESSES_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/wait.h>
# include "../includes/pipes.h"
# include "../includes/split_pass.h"
# include "../.dependencies/libft/libft.h"

int		enter_process_op(int fd[][2], int process_idx, char **argv, char **envp, int connections);
int		process_error(char ***args, char **cmd);
void	wait_all_child_finish(int id[], int child_qtd, int *status);

#endif