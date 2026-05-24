#include <unistd.h>
#include "tool.h"
#include "dict.h"
#include "convert_string.h"
#include <stdlib.h>

void	put_thousands(t_dict *dict, int thousands, char *num_s)
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
	search_exact_t(dict, temp, 3 * thousands + 1, num_s);
	free(temp);
}

// 1. check if we have any exact match in dict eg 42: hello world
// 2. if number is less than thousand handle it accordinly
// 3. else slice the number and handle it in power of thousands
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
		if (!is_100(num_s, num_len) && search_exact(dict, num_s, num_len))
			return ;
		tens = (num_len - 1) % 3;
		if (!put_hundreds(dict, num_s, tens + 1, thousands))
			put_thousands(dict, thousands, num_s);
		num_len -= tens + 1;
		num_s += tens + 1;
		thousands--;
	}
}
