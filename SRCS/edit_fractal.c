/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguirama <fguirama@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 18:40:00 by fguirama          #+#    #+#             */
/*   Updated: 2023/01/02 18:40:00 by fguirama         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	zoom(t_data *data, t_bool scroll_in, t_co co)
{
	double		scale;
	double		max_iter;

	co.x = (double)co.x / (WIN / (data->f->plan.end.x - \
data->f->plan.start.x)) + data->f->plan.start.x;
	co.y = (double)co.y / (WIN / (data->f->plan.end.y - \
data->f->plan.start.y)) * -1 + data->f->plan.end.y;
	scale = 1.3;
	max_iter = 1.03;
	if (scroll_in)
		scale = 1 / scale;
	if (!scroll_in)
		max_iter = 1 / 1.02;
	data->f->max_iter = (int)((double)data->f->max_iter * max_iter);
	data->f->plan.start.x = cross_multi_plan(co.x, data->f->plan.start.x, \
scale);
	data->f->plan.start.y = cross_multi_plan(co.y, data->f->plan.start.y, \
scale);
	data->f->plan.end.x = cross_multi_plan(co.x, data->f->plan.end.x, scale);
	data->f->plan.end.y = cross_multi_plan(co.y, data->f->plan.end.y, scale);
	data->zoom_size++;
}

double	cross_multi_plan(double start, double end, double scale)
{
	return (start + ((end - start) * scale));
}

void	move(t_data *data, int x, int y)
{
	t_co	co;

	co.x = (data->prev_pos.x - x) / WIN * fabs(data->f->plan.end.x - \
data->f->plan.start.x);
	data->f->plan.start.x += co.x;
	data->f->plan.end.x += co.x;
	co.y = (data->prev_pos.y - y) / WIN * fabs(data->f->plan.end.y - \
data->f->plan.start.y);
	data->f->plan.start.y += co.y;
	data->f->plan.end.y += co.y;
	data->prev_pos = (t_co){x, y};
}

void	edit_iter(t_data *data, double j)
{
	double	res;

	res = data->f->max_iter + j;
	if (res < 10 || res > 500)
		return ;
	data->f->max_iter = res;
	data->update = TRUE;
}

t_co	get_r(t_fractal *f)
{
	return ((t_co){(f->plan.end.x - f->plan.start.x) / (WIN - 1), (\
f->plan.end.y - f->plan.start.y) / (WIN - 1)});
}
