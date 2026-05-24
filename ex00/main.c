/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbartosz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 13:57:34 by kbartosz          #+#    #+#             */
/*   Updated: 2026/05/24 22:35:40 by kbartosz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdbool.h>

#include "convert_string.h"
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

int	is_args_valid(int argc, char *argv[], char **dict_path)
{
	if (argc < 2 || argc > 3)
	{
		ft_putstr("Error\n", STDERR_FILENO);
		return (false);
	}
	if (argc == 3)
		*dict_path = argv[1];
	else
		*dict_path = "dict/numbers.dict";
	if (!is_num_arg_valid(argv[argc - 1]))
		return (false);
	return (true);
}

int	is_num_only_zero(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] == '0')
	{
		i++;
	}
	return (!str[i]);
}

int	is_too_long(t_dict *dict, int len)
{
	int	i;

	len -= ((len - 1) % 3);
	i = -1;
	while (++i < dict -> size)
	{
		if (dict -> numlens[i] >= len)
			return (0);
	}
	return (1);
}

/**
 * mode 1: only 1 argument: number

 * mode 2: 1st argument: dict_path, 2nd argument: number
 */
int	main(int argc, char *argv[])
{
	t_dict	*dict;
	char	*dict_path;

	if (!is_args_valid(argc, argv, &dict_path))
		return (1);
	dict = create_dict();
	if (open_dict(dict, dict_path))
	{
		ft_putstr("Dict Error\n", STDERR_FILENO);
		return (1);
	}
	if (is_num_only_zero(argv[argc - 1]))
	{
		put_digit(dict, "0");
		write(STDOUT_FILENO, "\n", 1);
		return (0);
	}
	if (is_too_long(dict, _strlen(argv[argc -1])))
		ft_putstr("Dict Error\n", STDERR_FILENO);
	if (is_too_long(dict, _strlen(argv[argc -1])))
		return (1);
	convert_s(dict, argv[argc - 1], _strlen(argv[argc - 1]));
	write(STDOUT_FILENO, "\n", 1);
	delete_dict(dict);
	return (0);
}
