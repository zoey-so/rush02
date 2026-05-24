/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_string2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbartosz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/24 22:28:55 by kbartosz          #+#    #+#             */
/*   Updated: 2026/05/24 22:33:08 by kbartosz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "tool.h"
#include "dict.h"
#include "convert_string.h"
#include <stdlib.h>

int	search_exact_tens(t_dict *dict, char *num_s, int num_len, char *real_num)
{
	int	size;
	int	i;

	size = dict -> size;
	i = -1;
	while (++i < size)
	{
		if (dict -> numlens[i] == num_len)
		{
			if (!ft_strncmp(num_s, dict -> nums[i], num_len))
			{
				ft_putstr(dict -> strs[i], STDOUT_FILENO);
				if (*(real_num + 1) != '0')
					write(1, " ", 1);
				return (1);
			}
		}
	}
	return (0);
}

int	search_exact_t(t_dict *dict, char *num_s, int num_len, char *real_num)
{
	int	size;
	int	i;

	size = dict -> size;
	i = -1;
	while (++i < size)
	{
		if (dict -> numlens[i] == num_len)
		{
			if (!ft_strncmp(num_s, dict -> nums[i], num_len))
			{
				ft_putstr(dict -> strs[i], STDOUT_FILENO);
				if (!is_last(real_num))
					write(1, " ", 1);
				return (1);
			}
		}
	}
	return (0);
}

int	search_exact(t_dict *dict, char *num_s, int num_len)
{
	int	size;
	int	i;

	size = dict -> size;
	i = -1;
	while (++i < size)
	{
		if (dict -> numlens[i] == num_len)
		{
			if (!ft_strncmp(num_s, dict -> nums[i], num_len))
			{
				ft_putstr(dict -> strs[i], STDOUT_FILENO);
				if (*(num_s + num_len))
					write(1, " ", 1);
				return (1);
			}
		}
	}
	return (0);
}

// parse to check only one digit numbers if the char matches print the value
void	put_digit(t_dict *dict, char *num_s)
{
	int	size;
	int	i;

	size = dict -> size;
	i = -1;
	while (++i < size)
	{
		if (dict -> numlens[i] == 1)
		{
			if (dict -> nums[i][0] == *num_s)
			{
				ft_putstr(dict -> strs[i], STDOUT_FILENO);
				if (*(num_s + 1))
					write(1, " ", 1);
				return ;
			}
		}
	}
}

//print the dicts value for 100 
void	put_100(t_dict *dict, char *num_s)
{
	int	size;
	int	i;

	size = dict -> size;
	i = -1;
	while (++i < size)
	{
		if (dict -> numlens[i] == 3)
		{
			if (!ft_strncmp(dict -> nums[i], "100", 3))
			{
				ft_putstr(dict -> strs[i], STDOUT_FILENO);
				if (!is_last(num_s) || _strlen(num_s) != 3)
					write(1, " ", 1);
			}
		}
	}
}
