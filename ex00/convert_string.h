/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_string.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbartosz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/24 22:29:13 by kbartosz          #+#    #+#             */
/*   Updated: 2026/05/24 22:30:26 by kbartosz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONVERT_STRING_H
# define CONVERT_STRING_H

# include "dict.h"

int		is_last(char *num_s);

int		search_exact_t(t_dict *dict, char *num_s, int num_len, char *real_num);

int		search_exact_tens(t_dict *dict, char *num_s, int num_len,
			char *real_num);

int		search_exact(t_dict *dict, char *num_s, int num_len);

void	put_digit(t_dict *dict, char *num_s);

void	put_100(t_dict *dict, char *num_s);

void	put_tens(t_dict *dict, char *num_s, int num_len);

int		check_thousands(t_dict *dict, char *num_s, int num_len, int thousands);

int		check_hundreds(t_dict *dict, char *num_s);

int		is_100(char *num_s, int len);

int		put_hundreds(t_dict *dict, char *num_s, int num_len, int thousands);

void	put_thousands(t_dict *dict, int thousands, char *num_s);

#endif
