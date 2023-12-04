/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_menu.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguirama <fguirama@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 16:22:44 by fguirama          #+#    #+#             */
/*   Updated: 2022/12/12 16:22:45 by fguirama         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	set_page(t_data *data, int page)
{
	static t_fractals	menu[3][4] = {\
				{MANDELBROT, JULIA, CELTIC, BURNING_SHIP}, \
				{BUFFALO, BURNING_JULIA, JULIA3, CELTIC_MANDELBAR}, \
				{PERPENDICULAR_CELTIC, HEART, MANDELBAR, CELTIC_MANDELBROT}};

	if (page < 0)
		page = 2;
	page %= 3;
	data->menus[POS_1] = menu[page][POS_1];
	data->menus[POS_2] = menu[page][POS_2];
	data->menus[POS_3] = menu[page][POS_3];
	data->menus[POS_4] = menu[page][POS_4];
	data->page = page;
	set_menu(data);
}
