/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbartosz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 13:57:34 by kbartosz          #+#    #+#             */
/*   Updated: 2026/05/23 15:52:14 by kbartosz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	load_dict(struct *d);
int validate_ref_dict_arg(char *dict_name);
int validate_num_arg(char *num_arg);

void	ft_putstr(char *str, int fildes)
{
	int	i;
	
	i = 0;
	while(str[i])
		i++;
	write(fildes, str, i);
}

int	main(int argc, char *argvp[])
{
	if (argc < 2 || argc > 3)
		return (0);

	// validate args first
	// if wrong exit early

	if (argc == 3)
	{
		if(!is_ref_dict_arg_valid(argv[1]))     // if file exists ?? or...what?
		{
			ft_putstr("XD ??? error", STDOUT_FILENO); // TODO WHAT ERROR MESSAGE HERE
			return (1);                      
		}
		if(!validate_num_arg(argv[2]))        // if only digits (have to be valid, positive integer)
		{
			ft_putstr("Error", STDOUT_FILENO);
			return (1);
		}
	}
	else
	{
		if(!validate_nums_arg(argv[1]))
		{
			ft_putstr("Error", STDOUT_FILENO);
			return (1);
		}
	}

	// TODO validate_num_arg  and validate_ref_dict_arg functions
	
	/* expected struct:
	struct dict
	{
		int	size;
		char **nums;
		char **strs;
	}
	*/
	// TODO Declare pointer to struct.
	// TODO initialize this pointer - (norminette 2 steps)
	// TODO CALL function that will calculate how many correct lines are in dict_file.
	// TODO handle error from calculate function
	// load dict_file to memory:
	// handle error from load
	if (!load_dict(struct *d);
		ft_putstr("Dict Error\n", STDOUT_FILENO);
	// after dict validation:


	// one arg -> search dict
	// search_dict(str *num)
	
	// TODO free EVERYTHING allocated
}

