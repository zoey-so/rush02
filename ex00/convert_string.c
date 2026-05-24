#include <unistd.h>
#include "tool.h"

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
			if (dict -> *nums[i] == c)
			{
				ft_putstr(dict -> strs[i], STDOUT_FILENO);
				return (1);
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
			if (!strncmp(dict -> nums[i], "100"))
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

	if (exact_match(dict, num_s, num_len))
		return ;
	temp[0] = num_s[0];
	temp[1] = '0';
	(exact_match(dict, temp, 2));
	if (*(num_s + 1) != '0')
		put_digit(dict, *(num_s + 1));
}

// 1. search for exact match of hundred number
// 2. if no exact print digit number and hundreds string
// 3. if second char not 0 - go to handling tens function
// 4. else print the 1-9
void	put_hundreds(t_dict *dict, char *num_s, int num_len)
{
	if (search_exact(dict, num_s, num_len))
		return ;
	if (num_len == 3)
	{
		put_digit(dict, num_s[0]);
		put_100(dict);
		num_len--;
		while (num_len > 0 && *(++num_s) == '0')
			num_len--;
	}
	if (num_len == 2)
	{
		put_tens(dict, num_s, num_len);
		return ;
	}
	else if (num_len == 1)
		put_digit(dict, num_s[0]);
}

void	put_thousands(t_dict *dict, char *num_s, int thousands)
{

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

	if (num_len < 4)
		put_hundreds(dict, num_s, num_len);
	else
	{
		thousands = (num_len - 1) / 3;
		while (thousands > 0)
		{
			while (*num_s == '0')
			{
				num_s++;
				num_len--;
			}
			if ((search_exact(dict, num_s, num_len)))
				return ;
			tens = (num_len - 1) % 3;
			put_hundreds(dict, num_s, tens + 1);
			put_thousands(dict, num_s, thousands);
			num_len -= 3;
			num_s += 3;
			thousands--;
		}
	}
}
