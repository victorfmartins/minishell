/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 21:35:14 by asoler            #+#    #+#             */
/*   Updated: 2022/11/02 19:05:07 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exit_program(t_data *data)
{
	free_and_count_array(data->path, free);
	free_hash_table(data);
	free(data->line);
	(void)data;
	exit(0);
}
