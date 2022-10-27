/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 21:21:37 by asoler            #+#    #+#             */
/*   Updated: 2022/10/27 13:57:08 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../../includes/minishell.h"
# include "../includes/pipex.h"

int	verify_access(char *path, int mode)
{
	if (access(path, mode) < 0)
	{
		if (mode == R_OK || mode == W_OK)
			ft_printf("bash: %s: %s\n", path, strerror(errno));
		return (0);
	}
	return (1);
}
