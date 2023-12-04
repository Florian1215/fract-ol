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

static double	cross_multi(double start, double end, double scale);

void	zoom(t_data *data, t_bool scroll_in, t_co co)
{
	static int	i = 0;
	double		scale;

	if (scroll_in)
		scale = 1 / 1.3;
	else
		scale = 1.3;
	i++;
	if (i > 5)
	{
		i = 0;
		data->f->max_iter += 7 * (-1 * (scale > 1) + (scale < 1));
	}
	data->f->plan.start.x = cross_multi(co.x, data->f->plan.start.x, scale);
	data->f->plan.start.y = cross_multi(co.y, data->f->plan.start.y, scale);
	data->f->plan.end.x = cross_multi(co.x, data->f->plan.end.x, scale);
	data->f->plan.end.y = cross_multi(co.y, data->f->plan.end.y, scale);
}

static double	cross_multi(double start, double end, double scale)
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
