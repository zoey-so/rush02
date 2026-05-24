/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugusty <paugusty@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 13:17:27 by paugusty          #+#    #+#             */
/*   Updated: 2026/05/23 18:23:09 by paugusty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DICT_H
# define DICT_H

typedef struct s_dict
{
	int		bufsize;
	int		size;
	int		*numlens;
	char	**nums;
	char	**strs;
}	t_dict;

int	open_dict(char *dict_pathname);

#endif
