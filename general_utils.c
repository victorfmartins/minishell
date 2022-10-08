/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 22:16:57 by asoler            #+#    #+#             */
/*   Updated: 2022/10/08 19:46:43 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	free_and_count_array(char **array, void (*f)(void *))
{
	int	n;

	n = 0;
	while (array[n])
	{
		if (f)
			f(array[n]);
		n++;
	}
	if (f)
		f(array);
	return (n);
}
