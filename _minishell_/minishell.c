/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 22:57:17 by asoler            #+#    #+#             */
/*   Updated: 2022/12/03 23:50:51 by asoler           ###   ########.fr       */
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
			// - tmbm passando numero como nome da var
			// export 1=sdfsd
			// bash: export: `1=sdfsd': not a valid identifier
			// export HH+JJ | ls
			// bash: export: `HH+JJ': not a valid identifier
// - unset -> is not working
// // try these:
		// export PATH=$PATH:/something/bin
