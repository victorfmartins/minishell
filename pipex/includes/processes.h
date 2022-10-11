/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 16:25:37 by vfranco-          #+#    #+#             */
/*   Updated: 2022/10/11 03:02:18 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROCESSES_H
# define PROCESSES_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/wait.h>
# include "pipes.h"
# include "split_pass.h"
# include "../../includes/libft.h"

int		enter_process_op(int fd[][2], int process_idx, char **argv, char **envp, int connections);
int		process_error(char ***args, char **cmd);
void	wait_all_child_finish(int id[], int child_qtd, int *status);

#endif