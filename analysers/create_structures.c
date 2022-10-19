/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_structures.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfranco- <vfranco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 22:02:17 by vfranco-          #+#    #+#             */
/*   Updated: 2022/10/19 19:33:18 by vfranco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_file	*ft_filenew(char *name, int type)
{
	t_file	*lst;

	lst = malloc(sizeof(t_file));
	if (!lst)
		return (NULL);
	lst->name = name;
	lst->type = type;
	lst->next = NULL;
	return (lst);
}

void	ft_file_addback(t_file **lst, t_file *new)
{
	t_file	*p;

	if (!lst || !new)
		return ;
	if (!(*lst))
		*lst = new;
	else
	{
		p = *lst;
		while (p->next)
			p = p->next;
		p->next = new;
	}
}

t_cmd	*ft_cmdnew(char *frase)
{
	t_cmd	*lst;

	lst = malloc(sizeof(t_cmd));
	if (!lst)
		return (NULL);
	lst->line = frase;
	lst->next = NULL;
	return (lst);
}

void	ft_cmd_addback(t_cmd **lst, t_cmd *new)
{
	t_cmd	*p;

	if (!lst || !new)
		return ;
	if (!(*lst))
		*lst = new;
	else
	{
		p = *lst;
		while (p->next)
			p = p->next;
		p->next = new;
	}
}

// int	main(void)
// {
// 	t_cmd	*cmd;
// 	t_cmd	*p;
// 	t_cmd	*p_next;
// 	t_file	*file;

// 	cmd = NULL;
// 	ft_cmd_addback(&cmd, ft_cmdnew("victor "));
// 	ft_cmd_addback(&cmd, ft_cmdnew("franco "));
// 	ft_cmd_addback(&cmd, ft_cmdnew("martins "));
// 	p = cmd;
// 	while (p)
// 	{
// 		p_next = p->next;
// 		file = NULL;
// 		ft_file_addback(&file, ft_filenew("(in1) ", DIR));
// 		ft_file_addback(&file, ft_filenew("(in2) ", DIR));
// 		ft_file_addback(&file, ft_filenew("(in3)", DIR));
// 		p->infiles = file;
// 		file = NULL;
// 		ft_file_addback(&file, ft_filenew("(out1) ", REDIR));
// 		ft_file_addback(&file, ft_filenew("(out2) ", REDIR));
// 		ft_file_addback(&file, ft_filenew("(out3)", REDIR));
// 		p->outfiles = file;
// 		p = p_next;
// 	}
// 	print_cmd_lst(cmd);
// 	ft_cmdclear(&cmd, free);
// }
