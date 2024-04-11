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

// TODO fix bug
void	set_page(t_data *data, int page, t_bool update)
{
	static t_fractals	menu[3][4] = {\
				{MANDELBROT, JULIA, CELTIC, BURNING_SHIP}, \
				{BUFFALO, BURNING_JULIA, JULIA3, CELTIC_MANDELBAR}, \
				{PERPENDICULAR_CELTIC, HEART, MANDELBAR, CELTIC_MANDELBROT}};

	if (page < 0)
		page = 2;
	page %= 3;
	if (update)
	{
		data->f = data->fractals + (page * 4);
		set_page_value(data);
	}
	data->menus[POS_1] = menu[page][POS_1];
	data->menus[POS_2] = menu[page][POS_2];
	data->menus[POS_3] = menu[page][POS_3];
	data->menus[POS_4] = menu[page][POS_4];
	data->page = page;
	set_menu(data);
}

void	set_page_value(t_data *data)
{
	if (data->f->set < BUFFALO)
		data->page = 0;
	else if (data->f->set < PERPENDICULAR_CELTIC)
		data->page = 1;
	else
		data->page = 2;
	init_hovers(data);
}
