/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbartosz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 13:57:34 by kbartosz          #+#    #+#             */
/*   Updated: 2026/05/24 20:17:06 by kbartosz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdbool.h>
#include "dict.h"
#include "tool.h"

void	convert_s(t_dict *dict, char *num_s, int num_len);
int		open_dict(t_dict *dict, char *pathname);

/* if only digits (have to be valid, positive integer)
    version not allowing leading zeroes:*/
int	is_num_arg_valid(char *num_arg)
{
	int	i;

	i = 0;
	if (!num_arg[0])
	{
		ft_putstr("Error\n", STDERR_FILENO);
		return (false);
	}
	if (num_arg[i] == '0')
		if (num_arg[i + 1])
			return (false);
	while (num_arg[i])
	{
		if (num_arg[i] < '0' || num_arg[i] > '9')
		{
			ft_putstr("Error\n", STDERR_FILENO);
			return (false);
		}
		i++;
	}
	return (true);
}

/**
 * mode 1: only 1 argument: number
 * mode 2: 1st argument: dict_path, 2nd argument: number
 */
int	main(int argc, char *argv[])
{
	t_dict	*dict;
	char	*dict_path;

	if (argc < 2 || argc > 3)
	{
		ft_putstr("Error\n", STDERR_FILENO);
		return (1);
	}
	if (argc == 3)
		dict_path = argv[1];
	else
		dict_path = "dict/numbers.dict";
	if (!is_num_arg_valid(argv[argc - 1]))
		return (1);
	dict = create_dict();
	if (open_dict(dict, dict_path))
	{
		ft_putstr("Dict Error\n", STDERR_FILENO);
		return (1);
	}
	convert_s(dict, argv[argc - 1], _strlen(argv[argc - 1]));
	delete_dict(dict);
	return (0);
}
