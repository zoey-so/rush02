/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugusty <paugusty@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 15:58:40 by paugusty          #+#    #+#             */
/*   Updated: 2026/05/23 18:23:16 by paugusty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRING_H
# define STRING_H

typedef struct s_string
{
	int		bufsize;
	int		size;
	char	*str;
}	t_string;

t_string	*create_string(void);
void		add_char(t_string *str, char ch);

#endif
