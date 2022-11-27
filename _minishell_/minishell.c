/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 22:57:17 by asoler            #+#    #+#             */
/*   Updated: 2022/11/27 14:12:19 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	alloc_env_hash(envp, &data);
	while (1)
	{
		set_exec_paths(&data);
		prompt(&data);
	}
	(void)argc;
	(void)argv;
}

// [TODO]
// - testar variaveis vazias
// - export deve funcionar unicamente com formato key=value
		// - quando usado com pipe retorna menssagem
			// export HH+JJ | ls
			// bash: export: `HH+JJ': not a valid identifier
			// avaliações  mini_merge  pipeline  pipex_adapt  printa_struc  print_data_struct  projetos_fase1
// - unset -> seg fault
