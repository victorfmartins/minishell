/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfranco- <vfranco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 22:57:17 by asoler            #+#    #+#             */
/*   Updated: 2022/10/17 06:31:35 by vfranco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	// alloc_env_hash(envp, &data);
	//print_table(data.hash_table);
	data.envp = envp;
	// set_exec_paths(&data); // observação: colocar dentro do loop para caso o usuario altere algum path
	while (1)
	{
		prompt(&data);
	}
	(void)argc;
	(void)argv;
}
