/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_pass.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfranco- <vfranco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 12:38:05 by vfranco-          #+#    #+#             */
/*   Updated: 2022/10/07 17:21:21 by vfranco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/split_pass.h"

static void	build_word(char ***arr, char **cpy, int word, int word_len)
{
	(*arr)[word] = malloc(sizeof(char) * (word_len + 1));
	if (!(*arr)[word])
		return (free_until((*arr), word - 1));
	if (**cpy == '\'' && *(*cpy + word_len - 1) == '\'')
		ft_strlcpy((*arr)[word], *cpy + 1, word_len - 1);
	else
		ft_strlcpy((*arr)[word], *cpy, word_len + 1);
	*cpy = *cpy + word_len;
}

static void	build_arr(char ***arr, char *cpy, char c, char l)
{
	int		words_qtd;
	int		word_len;
	int		word;

	words_qtd = count_words(cpy, c, l);
	(*arr) = malloc(sizeof(char *) * (words_qtd + 1));
	if (!(*arr))
		return ;
	word_len = 0;
	word = 0;
	while (word < words_qtd)
	{
		word_len = word_lenght(cpy, c, l);
		build_word(arr, &cpy, word, word_len);
		while (cpy && *cpy == c)
			cpy++;
		word++;
	}
	(*arr)[word] = NULL;
	return ;
}

char	**ft_split_pass(char const *s, char c, char l)
{
	char	*cpy;
	char	**arr;

	cpy = ft_strtrimc(s, c);
	if (!cpy || c == l)
	{
		free(cpy);
		return (NULL);
	}
	build_arr(&arr, cpy, c, l);
	free(cpy);
	return (arr);
}
