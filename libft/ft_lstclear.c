/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfranco- <vfranco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 12:41:50 by vfranco-          #+#    #+#             */
/*   Updated: 2022/10/19 15:21:14 by vfranco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*p;
	t_list	*p_next;

	if (!lst || !del)
		return ;
	p = *lst;
	while (p)
	{
		p_next = p->next;
		ft_lstdelone(p, del);
		p = p_next;
	}
	*lst = NULL;
}
