/* *************************************:************************************* */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbartosz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 13:57:34 by kbartosz          #+#    #+#             */
/*   Updated: 2026/05/24 12:29:52 by kbartosz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdbool.h>
#include "dict.h"

void	convert_s(t_dict *dict, char *num_s, int num_len)
int		load_dict(s_dict *d);

int	ft_strlen(char *str);
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

/**
 * @param fildes File descriptor:
 * 1: STDOUT_FILENO Standard output
 * 2: STDERR_FILENO Standard error output
 */
void	ft_putstr(char *str, int fildes)
{
	write(fildes, str, ft_strlen(str));
}

int		validate_ref_dict_arg(char *dict_name)
{
	return (true);     // TODO should some validation be before calling open_dict()
}

int	ft_strncmp(char *s1, char *s2, unsigned int n)
{
	unsigned int	i;
	int				r;

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

// if only digits (have to be valid, positive integer)
int	validate_num_arg(char *num_arg)
{
	int	i;

	i = 0;
	while (num_arg[i])
		if (num_arg[i] < '0' || num_arg[i] > '9')
			return (false);
	return (true);
}

int	is_args_valid(int mode, char **argv)
{
	// TODO  validate_ref_dict_arg functions
	if (mode == 2 && !is_ref_dict_arg_valid(argv[1])) // check if file exists ?? or...what?
	{
		ft_putstr("XD ??? error", STDERR_FILENO); // TODO WHAT ERROR MESSAGE HERE
		return (false);
	}
	if (!is_num_arg_valid(argv[mode - 1]))
	{
		ft_putstr("Error", STDERR_FILENO);
		return (false);
	}
	return (true);
}

int	main(int argc, char *argvp[])
{
	int		mode;
	s_dict	*dict;

	if (argc < 2 || argc > 3)
		return (0);
	if (argc == 3)
		mode = 2; // 2 arguments: dict and num
	else
		mode = 1; // 1 argument only: num
	if (!is_args_valid(mode, argv))
		return (0);
	// TODO if mode == 2 pass other dict file to open
	dict = NULL;
	if (!open_dict(dict))
	{
		ft_putstr("Dict Error\n", STDERR_FILENO);
		return (0);
	}
	// TODO reconcile error (returns, and messages)
	convert_s(dict, argv[mode], strlen(argv[mode]));
	// TODO free EVERYTHING allocated
}
