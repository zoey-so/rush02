/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugusty <paugusty@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/24 14:38:27 by paugusty          #+#    #+#             */
/*   Updated: 2026/05/24 15:15:07 by paugusty         ###   ########.fr       */
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

int	parse_dict(int fd, t_dict *dict, t_string *num, t_string *str)
{
	int			prev;
	int			read_count;
	char		buf[1];

	prev = P_NL;
	while (1)
	{
		read_count = read(fd, buf, 1);
		if (read_count < 0)
			return (-1);
		if (read_count == 0 && prev == P_NL)
			return (0);
		if (read_count == 0)
			return (-1);
		if (prev == P_NL && buf[0] == '\n')
		{
		}
		else if (prev == P_NL && buf[0] >= '0' && buf[0] <= '9')
		{
			prev = P_DIGIT;
			add_char(num, buf[0]);
		}
		else if (prev == P_DIGIT && buf[0] >= '0' && buf[0] <= '9')
			add_char(num, buf[0]);
		else if (prev == P_DIGIT && buf[0] == ' ')
		{
			prev = P_SPACE1;
			add_char(num, '\0');
		}
		else if (prev == P_DIGIT && buf[0] == ':')
		{
			prev = P_COLON;
			add_char(num, '\0');
		}
		else if (prev == P_SPACE1 && buf[0] == ' ')
		{
		}
		else if (prev == P_SPACE1 && buf[0] == ':')
			prev = P_COLON;
		else if (prev == P_COLON && buf[0] == ' ')
			prev = P_SPACE2;
		else if ((prev == P_COLON || prev == P_SPACE2) && buf[0] == '\n')
			return (-1);
		else if (prev == P_SPACE2 && buf[0] == ' ')
		{
		}
		else if (prev == P_COLON || prev == P_SPACE2)
		{
			prev = P_STR;
			add_char(str, buf[0]);
		}
		else if (prev == P_STR && buf[0] == '\n')
		{
			prev = P_NL;
			add_char(str, '\0');
			add_elem(dict, num->str, str->str);
			num->size = 0;
			str->size = 0;
		}
		else if (prev == P_STR && buf[0] >= ' ' && buf[0] <= '~')
			add_char(str, buf[0]);
		else
			return (-1);
	}
}
