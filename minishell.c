/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 22:57:17 by asoler            #+#    #+#             */
/*   Updated: 2022/10/08 19:11:35 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	data.hash_table = ft_calloc(sizeof(t_env), TABLE_SIZE);
	alloc_env_hash(envp, &data.hash_table);
	// print_table(data.hash_table);
	set_exec_paths(&data);
	while (1)
	{
		prompt(&data);
	}
	(void)argc;
	(void)argv;
}
