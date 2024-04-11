/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguirama <fguirama@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 21:11:00 by fguirama          #+#    #+#             */
/*   Updated: 2024/04/11 21:11:00 by fguirama         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

double	side_line(t_co color_line, t_co co)
{
	return (0 - color_line.x) * (co.x - 0) + ((color_line.y * -1) + 0) * (co.y - color_line.x);
}
