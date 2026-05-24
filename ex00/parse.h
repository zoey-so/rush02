/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugusty <paugusty@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/24 14:55:43 by paugusty          #+#    #+#             */
/*   Updated: 2026/05/24 14:55:46 by paugusty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "dict.h"
# include "string.h"

int	parse_dict(int fd, t_dict *dict, t_string *num, t_string *str);

#endif
