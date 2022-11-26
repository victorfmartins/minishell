/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 22:57:17 by asoler            #+#    #+#             */
/*   Updated: 2022/11/02 21:23:41 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	alloc_env_hash(envp, &data);
	data.envp = envp;
	while (1)
	{
		set_exec_paths(&data);
		// print_table(data.hash_table);
		prompt(&data);
		// data.envp = update_env_vars(data); -> deve atualizar para passar no execve
	}
	(void)argc;
	(void)argv;
}

// [TODO]
// - testar variaveis vazias
// - começar codando unset e export como comando simples
// - builtins(echo, exit, cd, unset e export) devem continuar funcionando mesmo quando de PATH foi unset
	// - echo(manda caminho absoluto em execve), unset e export executa mas tambem mostra menssagem de erro -cut-
	// - env não executa -> env é executado em execve normal
			// bash: env: Arquivo ou diretório inexistente
			// bash: cut: Arquivo ou diretório inexistente
// - tratar quanto PATH foi unset

