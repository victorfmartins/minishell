/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_structures.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfranco- <vfranco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 19:30:27 by vfranco-          #+#    #+#             */
/*   Updated: 2022/10/19 20:50:04 by vfranco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_clear_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	ft_filedelone(t_file *file, void (*del)(void *))
{
	if (!file || !del)
		return ;
	free(file);
}

void	ft_fileclear(t_file **file, void (*del)(void *))
{
	t_file	*p;
	t_file	*p_next;

	if (!file || !del)
		return ;
	p = *file;
	while (p)
	{
		p_next = p->next;
		ft_filedelone(p, del);
		p = p_next;
	}
	*file = NULL;
}

void	ft_cmddelone(t_cmd *cmd, void (*del)(void *))
{
	if (!cmd || !del)
		return ;
	ft_fileclear(&cmd->infiles, del);
	ft_fileclear(&cmd->outfiles, del);
	ft_clear_array(cmd->args);
	free(cmd->exec_cmd);
	free(cmd);
}

void	ft_cmdclear(t_cmd **lst, void (*del)(void *))
{
	t_cmd	*p;
	t_cmd	*p_next;

	if (!lst || !del)
		return ;
	p = *lst;
	while (p)
	{
		p_next = p->next;
		ft_cmddelone(p, del);
		p = p_next;
	}
	*lst = NULL;
}
