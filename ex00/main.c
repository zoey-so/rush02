/* *************************************:************************************* */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbartosz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 13:57:34 by kbartosz          #+#    #+#             */
/*   Updated: 2026/05/24 15:35:59 by kbartosz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdbool.h>
#include "dict.h"
#include "tool.h"

void	convert_s(t_dict *dict, char *num_s, int num_len);
int		open_dict(/*t_dict *d,*/ char *dist_path);

// if only digits (have to be valid, positive integer)
// version not allowing leading zeroes:
int	is_num_arg_valid(char *num_arg)
{
	int	i;

	i = 0;
	if (num_arg[i] == '0')
		return (false);
	while (num_arg[i])
		if (num_arg[i] < '0' || num_arg[i] > '9')
		{
			ft_putstr("Error", STDERR_FILENO);
			return (false);
		}
	return (true);
}

/**
 * mode 1: only 1 argument: number
 * mode 2: 1st argument: dict_path, 2nd argument: number
 */
int	main(int argc, char *argv[])
{
	int		mode;
	t_dict	*dict;
	char	*dict_path;

	if (argc < 2 || argc > 3)
		return (0);
	if (argc == 3)
	{
		mode = 2;
		dict_path = argv[1];
	}
	else
	{
		mode = 1;
		dict_path = "numbers.dict";
	}
	if (!is_num_arg_valid(argv[mode]))
		return (0);
	(void) dict = create_dict(); // TODO change after open_dict will allow to take this
	if (!open_dict(/*dict*,*/ dict_path))
	{
		ft_putstr("Dict Error\n", STDERR_FILENO);
		return (0);
	}
	// TODO reconcile error (returns, and messages)
	convert_s(dict, argv[mode], _strlen(argv[mode]));
	// TODO free EVERYTHING allocated
}
