/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbartosz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 13:57:34 by kbartosz          #+#    #+#             */
/*   Updated: 2026/05/23 18:15:34 by kbartosz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdbool.h>

int	load_dict(struct *d);
int validate_ref_dict_arg(char *dict_name);

// if only digits (have to be valid, positive integer)
int validate_num_arg(char *num_arg)
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
	if(mode == 2 && !is_ref_dict_arg_valid(argv[1])) // check if file exists ?? or...what?
	{
			ft_putstr("XD ??? error", STDOUT_FILENO); // TODO WHAT ERROR MESSAGE HERE
			return (false);                      
	}
	if(!is_num_arg_valid(argv[mode - 1])) 
	{
			ft_putstr("Error", STDOUT_FILENO);
			return (false);
	}
	return (true)
}

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
	int mode;

	if (argc < 2 || argc > 3)
		return (0);
	if (argc == 3)
		mode = 2   // 2 arguments: dict and num
	else
		mode = 1   // 1 argument only: num
	if (!is_args_valid(mode, argv))
		return (0);


	// TODO  and validate_ref_dict_arg functions
	
	/* expected struct:
	struct dict
	{
		int	size;
		int  num_len;
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

	// TODO

	// two args -> serch dict

	// TODO

	// TODO free EVERYTHING allocated
}

