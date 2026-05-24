/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugusty <paugusty@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 13:26:30 by paugusty          #+#    #+#             */
/*   Updated: 2026/05/23 20:44:44 by paugusty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#include "dict.h"
#include "string.h"
#include "tool.h"

#define P_NL 1
#define P_DIGIT 2
#define P_SPACE1 3
#define P_COLON 4
#define P_SPACE2 5
#define P_STR 6

static void	realloc_dict(t_dict *dict)
{
	int		*numlens_new;
	char	**nums_new;
	char	**strs_new;
	int		i;

	dict->bufsize *= 2;
	numlens_new = malloc(dict->bufsize * sizeof(int));
	nums_new = malloc(dict->bufsize * sizeof(char *));
	strs_new = malloc(dict->bufsize * sizeof(char *));
	i = -1;
	while (++i < dict->size)
	{
		numlens_new[i] = dict->numlens[i];
		nums_new[i] = dict->nums[i];
		strs_new[i] = dict->strs[i];
	}
	free(dict->numlens);
	free(dict->nums);
	free(dict->strs);
	dict->numlens = numlens_new;
	dict->nums = nums_new;
	dict->strs = strs_new;
}

static t_dict	*create_dict(void)
{
	t_dict	*result;

	result = malloc(sizeof(t_dict));
	result->bufsize = 1;
	result->size = 0;
	result->numlens = malloc(result->bufsize * sizeof(int));
	result->nums = malloc(result->bufsize * sizeof(char *));
	result->strs = malloc(result->bufsize * sizeof(char *));
	return (result);
}

static void	add_elem(t_dict *dict, char *num, char *str)
{
	if (dict->size == dict->bufsize)
		realloc_dict(dict);
	dict->nums[dict->size] = malloc(_strlen(num) + 1);
	dict->strs[dict->size] = malloc(_strlen(str) + 1);
	copy(dict->nums[dict->size], num);
	copy(dict->strs[dict->size], str);
	++dict->size;
}

static int	parse_dict(int fd, t_dict *dict, t_string *num, t_string *str)
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
#include <stdio.h>
printf("%s: %s\n", num->str, str->str);
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

int	open_dict(char *dict_pathname)
{
	int			fd;
	t_dict		*dict;
	t_string	*num;
	t_string	*str;
	int			parse_err;

	fd = open(dict_pathname, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr("Dict Error\n", 1);
		return (-1);
	}
	dict = create_dict();
	num = create_string();
	str = create_string();
	parse_err = parse_dict(fd, dict, num, str);
	close(fd);
	delete_string(num);
	delete_string(str);
	if (parse_err)
	{
		ft_putstr("Dict Error\n", 1);
		return (-1);
	}
	return (0);
}
