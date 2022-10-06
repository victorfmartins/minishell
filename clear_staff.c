/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_staff.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 22:16:57 by asoler            #+#    #+#             */
/*   Updated: 2022/09/28 01:20:31 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	free_table(char **table)
{
	char	**tmp;

	tmp = table;
	while (*table)
		free(*table++);
	free(tmp);
}
