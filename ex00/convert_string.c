#include <unistd.h>
#include "tool.h"
#include "dict.h"
#include <stdlib.h>

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
				return (1);
			}
		}
	}
	return (0);
}

// parse to check only one digit numbers if the char matches print the value
void	put_digit(t_dict *dict, char c)
{
	int	size;
	int	i;

	size = dict -> size;
	i = -1;
	while (++i < size)
	{
		if (dict -> numlens[i] == 1)
		{
			if (dict -> nums[i][0] == c)
			{
				ft_putstr(dict -> strs[i], STDOUT_FILENO);
				return ;
			}
		}
	}
}

//print the dicts value for 100 
void	put_100(t_dict *dict)
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
				ft_putstr(dict -> strs[i], STDOUT_FILENO);
		}
	}
}

// print tens numbers 
// 1. check if exact match like 42
// if not - print first digit with 0 ex. 40 then print digit
void	put_tens(t_dict *dict, char *num_s, int num_len)
{
	char	temp[2];

	if (search_exact(dict, num_s, num_len))
		return ;
	temp[0] = num_s[0];
	temp[1] = '0';
	search_exact(dict, temp, 2);
	if (*(num_s + 1) != '0')
		put_digit(dict, *(num_s + 1));
}

int	check_thousands(t_dict *dict, char *num_s, int num_len, int thousands)
{
	char	*temp;
	int		i;

	temp = (char *)malloc(sizeof(char) * (3 * thousands + num_len + 1));
	if (!temp)
		return (0);
	i = -1;
	while (++i < num_len)
		temp[i] = num_s[i];
	while (i < 3 * thousands + num_len)
		temp[i++] = '0';
	temp[i] = '\0';
	if (search_exact(dict, temp, 3 * thousands + num_len))
		i = 0;
	free(temp);
	if (!i)
		return (1);
	return (0);
}


int	check_hundreds(t_dict *dict, char *num_s)
{
	char	temp[4];

	temp[0] = num_s[0];
	temp[1] = '0';
	temp[2] = '0';
	temp[3] = '\0';
	if (search_exact(dict, temp, 3))
		return (1);
	return (0);
}

// 1. search for exact match of hundred number
// 2. if no exact print digit number and hundreds string
// 3. if second char not 0 - go to handling tens function
// 4. else print the 1-9
int	put_hundreds(t_dict *dict, char *num_s, int num_len, int thousands)
{
	if (check_thousands(dict, num_s, num_len, thousands))
		return (1);
	if (search_exact(dict, num_s, num_len))
		return (0);
	if (num_len == 3)
	{
		if (*num_s == '1' || !check_hundreds(dict, num_s))
		{
			put_digit(dict, num_s[0]);
			put_100(dict);
		}
		num_len--;
		while (num_len > 0 && *(++num_s) == '0')
			num_len--;
	}
	if (num_len == 2)
	{
		put_tens(dict, num_s, num_len);
		return (0);
	}
	else if (num_len == 1)
		put_digit(dict, num_s[0]);
	return (0);
}

void	put_thousands(t_dict *dict, int thousands)
{
	char	*temp;
	int		i;

	if (thousands == 0)
		return ;
	temp = (char *)malloc(sizeof(char) * (3 * thousands + 2));
	if (!temp)
		return ;
	temp[0] = '1';
	i = 0;
	while (++i < 3 * thousands + 1)
		temp[i] = '0';
	temp[i] = '\0';
	search_exact(dict, temp, 3 * thousands + 1);
	free(temp);
}


// 1. check if we have any exact match in dict eg 42: hello world
// 2. if number is less than thousand handle it accordinly
// 3. else slice the number and handle it in power of thousands
// TO DECIDE I prototype it to print the fragments of output directly from
// search_exact and put_hundreds and put_thousands, but we can also try to create a
// buffer and write to it. I think direct printing will be easier and more
// convenient.
void	convert_s(t_dict *dict, char *num_s, int num_len)
{
	int		thousands;
	int		tens;

	thousands = (num_len - 1) / 3;
	while (thousands >= 0 && num_len)
	{
		while (*num_s == '0' && (num_len - 1) / 3 == thousands)
		{
			num_s++;
			num_len--;
		}
		if ((num_len - 1) / 3 != thousands)
		{
			thousands = (num_len - 1) /3;
			continue ;
		}
		if ((search_exact(dict, num_s, num_len)))
			return ;
		tens = (num_len - 1) % 3;
		if (!put_hundreds(dict, num_s, tens + 1, thousands))
			put_thousands(dict, thousands);
		num_len -= tens + 1;
		num_s += tens + 1;
		thousands--;
	}
}

