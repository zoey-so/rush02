/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugusty <paugusty@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 19:15:41 by paugusty          #+#    #+#             */
/*   Updated: 2026/05/24 13:07:37 by kbartosz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOOL_H
# define TOOL_H

int		_strlen(char *str);
void	copy(char *dest, char *src);
void	add_char(t_string *str, char ch);
/**
 * @param fildes File descriptor:
 * 0: STDOUT_FILENO Standard output
 * 2: STDERR_FILENO Standard error output
 */
void	ft_putstr(char *str, int fildes);
int		ft_strncmp(char *s1, char *s2, unsigned int n);

#endif
