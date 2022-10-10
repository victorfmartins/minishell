/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfranco- <vfranco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 16:50:34 by vfranco-          #+#    #+#             */
/*   Updated: 2022/10/07 16:53:04 by vfranco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPLIT_UTILS_H
# define SPLIT_UTILS_H

# include "../.dependencies/libft/libft.h"

size_t	count_words(char *str, char c, char l);
size_t	word_lenght(char *str, char c, char l);
void	free_until(char **arr, int n);

#endif