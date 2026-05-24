/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugusty <paugusty@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 19:15:45 by paugusty          #+#    #+#             */
/*   Updated: 2026/05/24 13:16:45 by kbartosz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "tool.h"

int	_strlen(char *str)
{
	int	len;

	len = -1;
	while (str[++len])
		;
	return (len);
}

void	copy(char *dest, char *src)
{
	while (*src)
		*dest++ = *src++;
	*dest = '\0';
}

void    ft_putstr(char *str, int fildes)
{
    write(fildes, str, _strlen(str));
}

int ft_strncmp(char *s1, char *s2, unsigned int n)
{
    unsigned int    i;
    int             r;

    i = 0;
    r = 0;
    while (!r && i < n && (s1[i] || s2([i])))
    {
        r = (unsigned char) s1[i] - (unsigned char) s2[i];
        if (r)
            return (r);
        i++;
    }
    return (r);
}
