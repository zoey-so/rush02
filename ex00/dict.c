/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugusty <paugusty@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 13:26:30 by paugusty          #+#    #+#             */
/*   Updated: 2026/05/24 15:14:55 by paugusty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#include "parse.h"
#include "dict.h"
#include "string.h"
#include "tool.h"

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

t_dict	*create_dict(void)
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

void	delete_dict(t_dict *dict)
{
	int	i;

	i = -1;
	while (++i < dict->size)
	{
		free(dict->nums[i]);
		free(dict->strs[i]);
	}
	free(dict->numlens);
	free(dict->nums);
	free(dict->strs);
	free(dict);
}

void	add_elem(t_dict *dict, char *num, char *str)
{
	if (dict->size == dict->bufsize)
		realloc_dict(dict);
	dict->numlens[dict->size] = _strlen(num);
	dict->nums[dict->size] = malloc(_strlen(num) + 1);
	dict->strs[dict->size] = malloc(_strlen(str) + 1);
	copy(dict->nums[dict->size], num);
	copy(dict->strs[dict->size], str);
	++dict->size;
}

int	open_dict(t_dict *dict, char *dict_pathname)
{
	int			fd;
	t_string	*num;
	t_string	*str;
	int			parse_err;

	fd = open(dict_pathname, O_RDONLY);
	if (fd < 0)
		return (-1);
	num = create_string();
	str = create_string();
	parse_err = parse_dict(fd, dict, num, str);
	close(fd);
	delete_string(num);
	delete_string(str);
	if (parse_err)
		return (-1);
	return (0);
}
