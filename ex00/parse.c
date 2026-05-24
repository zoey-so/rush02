/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugusty <paugusty@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/24 14:38:27 by paugusty          #+#    #+#             */
/*   Updated: 2026/05/24 20:38:36 by kbartosz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "parse.h"
#include "dict.h"
#include "string.h"

#define P_NL 1
#define P_DIGIT 2
#define P_SPACE1 3
#define P_COLON 4
#define P_SPACE2 5
#define P_STR 6

int	st_digits(int *prev, char c, t_string *num)
{
	if (*prev == P_NL && c >= '0' && c <= '9')
	{
		*prev = P_DIGIT;
		add_char(num, c);
	}
	else if (*prev == P_DIGIT && c >= '0' && c <= '9')
		add_char(num, c);
	else if (*prev == P_DIGIT && c == ' ')
	{
		*prev = P_SPACE1;
		add_char(num, '\0');
	}
	else if (*prev == P_DIGIT && c == ':')
	{
		*prev = P_COLON;
		add_char(num, '\0');
	}
	else if (*prev == P_SPACE1 && c == ':')
		*prev = P_COLON;
	else
		return (1);
	return (0);
}

int	st_text(int *prev, char c, t_string *str)
{
	if (*prev == P_COLON && c == ' ')
		*prev = P_SPACE2;
	else if ((*prev == P_COLON || *prev == P_SPACE2) && c == '\n')
		return (-1);
	else if (*prev == P_COLON || *prev == P_SPACE2)
	{
		*prev = P_STR;
		add_char(str, c);
	}
	else if (*prev == P_STR && c >= ' ' && c <= '~')
		add_char(str, c);
	else
		return (1);
	return (0);
}

int	st_spaces(int prev, char c)
{
	if (prev == P_NL && c == '\n')
		return (0);
	if (prev == P_SPACE1 && c == ' ')
		return (0);
	if (prev == P_SPACE2 && c == ' ')
		return (0);
	return (-1);
}

void	save_elem(t_dict *dict, t_string *num, t_string *str)
{
	add_char(str, '\0');
	add_elem(dict, num->str, str->str);
	num->size = 0;
	str->size = 0;
}

int	parse_dict(int fd, t_dict *dict, t_string *num, t_string *str)
{
	int		prev;
	int		read_count;
	char	c;

	prev = P_NL;
	read_count = read(fd, &c, 1);
	while (read_count > 0)
	{
		if (prev == P_STR && c == '\n')
		{
			prev = P_NL;
			save_elem(dict, num, str);
		}
		else if (st_digits(&prev, c, num) == 1)
		{
			if (st_text(&prev, c, str) == 1)
			{
				if (st_spaces(prev, c) == -1)
					return (-1);
			}
		}
		read_count = read(fd, &c, 1);
	}
	return (read_count || prev != P_NL);
}
