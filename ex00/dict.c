/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugusty <paugusty@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 13:26:30 by paugusty          #+#    #+#             */
/*   Updated: 2026/05/23 13:26:34 by paugusty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#include "dict.h"
#include "string.h"

#define P_NL 1
#define P_DIGIT 2
#define P_SPACE1 3
#define P_COLON 4
#define P_SPACE2 5
#define P_STR 6

static int _strlen(char *str)
{
	int	len;

	len = -1;
	while (str[++len])
		;
	return (len);
}

static void	copy(char *dest, char *src)
{
	while (*src)
		*dest++ = *src++;
	*dest = '\0';
}

static void realloc_dict(t_dict *dict)
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

static t_dict	*create_dict()
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
	++dict->size;
	copy(dict->nums[dict->size], num);
	copy(dict->strs[dict->size], str);
}

static int parse_dict(int fd, t_dict *dict)
{
	int			prev;
	t_string	*num;
	t_string	*str;
	int			read_count;
	char		buf[1];

	prev = P_NL;
	num = create_string();
	str = create_string();
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
		if (prev == P_NL && buf[0] >= '0' && buf[0] <= '9')
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
			;
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
		}
		else if (prev == P_STR)
			add_char(str, buf[0]);
		else
			return (-1);
	}
}

int open_dict(char *dict_pathname)
{
	int		fd;
	t_dict	*dict;
	int		parse_err;

	dict = create_dict();
	fd = open(dict_pathname, O_RDONLY);
		if (fd < 0)
	{
		error("Dict Error\n");
		return (-1);
	}
	parse_err = parse_dict(fd, dict);
	close(fd);
	if (parse_err)
	{
		error("Dict Error\n");
		return (-1);
	}
	return (0);
}
