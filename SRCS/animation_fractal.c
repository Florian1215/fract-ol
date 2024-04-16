/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_fractals.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguirama <fguirama@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 16:54:00 by fguirama          #+#    #+#             */
/*   Updated: 2023/01/07 16:54:00 by fguirama         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	c_animation(t_data *data)
{
	if (data->i_c == FRAME_ANIMATION)
	{
		data->i_c = 0;
		data->c_animation = FALSE;
		data->f->c = data->f->animation_c.end;
		return ;
	}
	data->f->c.y = get_value(data->f->animation_c.start.y, \
data->f->animation_c.end.y, data->i_c);
	data->f->c.x = get_value(data->f->animation_c.start.x, \
data->f->animation_c.end.x, data->i_c);
	data->i_c++;
}

void	color_animation(t_data *data)
{
	if (data->i_color == FRAME_ANIMATION)
	{
		data->i_color = 0;
		data->color_animation = FALSE;
		return ;
	}
	if (data->in_menu)
	{
		data->color_co.x = get_value(WIN, 0, data->i_color);
	}
	else
	{
		data->color_co.x = get_value(0, WIN * 2, data->i_color);
		data->color_co.y = get_value(50, WIN * 2 + 50, data->i_color);
	}
	data->i_color++;
}

void	appearance_animation(t_data *data)
{
	data->i_appearance++;
	if (data->i_appearance == FRAME_ANIMATION)
	{
		data->appearance_animation = FALSE;
		data->i_appearance = 0;
		return ;
	}
}

void	bw_animation(t_data *data)
{
	if (data->i_bw == FRAME_ANIMATION)
	{
		data->bw_animation = FALSE;
		data->i_bw = 0;
		return ;
	}
	if (data->in_menu)
		data->bw_color_co.x = get_value(WIN, 0, data->i_bw);
	else
	{
		data->bw_color_co.x = get_value(0, WIN * 2, data->i_bw);
		data->bw_color_co.y = get_value(50, WIN * 2 + 50, data->i_bw);
	}
	data->i_bw++;
}

double	get_value(double a, double b, int i)
{
	const double	values[29] = {0.4, 1.7, 4.6, 9.8, 19, 32, 44.7, 54.7, 62.4, \
68.6, 73.6, 77.7, 81.2, 84.2, 86.8, 89, 90.9, 92.5, 93.9, 95.2, \
96.2, 97.1, 97.8, 98.5, 99, 99.4, 99.6, 99.8, 99.9};

	if (a > b)
		return (a - (values[i] * (a - b) / 100));
	else if (a < b)
		return ((values[i] * (b - a) / 100) + a);
	return (a);
}
