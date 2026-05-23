/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugusty <paugusty@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 15:58:48 by paugusty          #+#    #+#             */
/*   Updated: 2026/05/23 20:44:26 by paugusty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "string.h"

static void	realloc_string(t_string *str)
{
	char	*str_new;
	int		i;

	str->bufsize *= 2;
	str_new = malloc(str->bufsize);
	i = -1;
	while (++i < str->size)
	{
		str_new[i] = str->str[i];
	}
	free(str->str);
	str->str = str_new;
}

t_string	*create_string(void)
{
	t_string	*result;

	result = malloc(sizeof(t_string));
	result->bufsize = 1;
	result->size = 0;
	result->str = malloc(result->bufsize);
	return (result);
}

void	add_char(t_string *str, char ch)
{
	if (str->size == str->bufsize)
		realloc_string(str);
	str->str[str->size] = ch;
	++str->size;
}
