/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfranco- <vfranco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 09:36:08 by vfranco-          #+#    #+#             */
/*   Updated: 2022/10/07 17:21:29 by vfranco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/split_utils.h"

static void	pass_l(char **str, char c, char l, size_t *i)
{
	(*i)++;
	while (!(!(*str)[(*i)]
		|| ((*str)[(*i)] == l && (*i > 1 && (*str)[(*i) - 1] == '\\' ))
		|| ((*str)[(*i)] == l && ((*str)[(*i) + 1] == '\0'
			|| (*str)[(*i)++ + 1] == c))))
		(*i)++;
	return ;
}

size_t	count_words(char *str, char c, char l)
{
	size_t	i;
	size_t	words_qtd;

	words_qtd = (ft_strncmp(str, "", 1) != 0);
	i = 0;
	while (str[i])
	{
		if (str[i] == l)
			pass_l(&str, c, l, &i);
		if (str[i] == c)
		{
			while (str[i + 1] == c)
				i++;
			words_qtd++;
			i++;
		}
		if (str[i] != l)
			while (str[i] && str[i] != c)
				i++;
	}
	return (words_qtd);
}

size_t	word_lenght(char *str, char c, char l)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == l)
			pass_l(&str, c, l, &i);
		if (str[i] == c)
		{
			while (str[i + 1] == c)
				i++;
			break ;
		}
		if (str[i] != l)
			while (str[i] && str[i] != c)
				i++;
	}
	return (i);
}

void	free_until(char **arr, int n)
{
	while (n-- >= 0)
		free(arr[n]);
	return ;
}
