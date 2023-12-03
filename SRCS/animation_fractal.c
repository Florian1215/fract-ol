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

static void	compute_value(t_data *data, int i, int start_max_iter);

void	c_animation(t_data *data)
{
	if (data->i_c == 29)
	{
		data->i_c = 0;
		data->c_animate = FALSE;
		data->f->c = data->f->animation_c.end;
		return ;
	}
	data->f->c.y = get_value(data->f->animation_c.start.y, \
data->f->animation_c.end.y, data->i_c);
	data->f->c.x = get_value(data->f->animation_c.start.x, \
data->f->animation_c.end.x, data->i_c);
	data->i_c++;
}

void	reset_animation(t_data *data)
{
	static int	i = 0;
	static int	start_max_iter = 0;

	if (i == 0)
	{
		data->f->animation_plan = data->f->plan;
		start_max_iter = data->f->max_iter;
		data->f->max_iter = MAX_ITER;
	}
	else if (i == 29)
	{
		data->reset = FALSE;
		i = 0;
		return ;
	}
	compute_value(data, i, start_max_iter);
	i++;
}

static void	compute_value(t_data *data, int i, int start_max_iter)
{
	data->f->plan.start.x = get_value(data->f->animation_plan.start.x, \
data->f->plan_default.start.x, i);
	data->f->plan.start.y = get_value(data->f->animation_plan.start.y, \
data->f->plan_default.start.y, i);
	data->f->plan.end.x = get_value(data->f->animation_plan.end.x, \
data->f->plan_default.end.x, i);
	data->f->plan.end.y = get_value(data->f->animation_plan.end.y, \
data->f->plan_default.end.y, i);
	data->f->max_iter = get_value(MAX_ITER, start_max_iter, i);
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
