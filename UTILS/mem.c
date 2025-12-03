/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguirama <fguirama@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 16:11:00 by fguirama          #+#    #+#             */
/*   Updated: 2024/04/17 16:11:00 by fguirama         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_bool	mem_cmp(const void *s1, const void *s2)
{
	size_t	i;
	size_t	n;

	n = sizeof(*s1);
	i = 0;
	while (i < n && *(unsigned char *)(s1 + i) == *(unsigned char *)(s2 + i))
		i++;
	if (i != n)
		return (TRUE);
	return (FALSE);
}

void	ft_bzero(void *b, const size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		*(unsigned char *)(b + i) = 0;
		i++;
	}
}
