#include <unistd.h>
#include "tool.h"
#include "dict.h"
#include "convert_string.h"
#include <stdlib.h>

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
		put_digit(dict, num_s + 1);
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

int	is_100(char *num_s, int len)
{
	if (*num_s != '1')
		return (0);
	while (--len > 0)
	{
		if (num_s[len] != '0')
			return (0);
	}
	return (1);
}

// 1. search for exact match of hundred number
// 2. if no exact print digit number and hundreds string
// 3. if second char not 0 - go to handling tens function
// 4. else print the 1-9
int	put_hundreds(t_dict *dict, char *num_s, int num_len, int thousands)
{
	if (num_len == 3 && !is_100(num_s, 3) && !(num_len == 1 && *num_s == '1')
		&& check_thousands(dict, num_s, num_len, thousands))
		return (1);
	if (num_len == 3 && !is_100(num_s, num_len + thousands * 3)
		&& !is_100(num_s, 3) && search_exact(dict, num_s, num_len))
		return (0);
	if (num_len == 3)
	{
		if (*num_s == '1' || !check_hundreds(dict, num_s))
		{
			put_digit(dict, num_s);
			put_100(dict, num_s);
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
		put_digit(dict, num_s);
	return (0);
}
