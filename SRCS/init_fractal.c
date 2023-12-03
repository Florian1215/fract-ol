/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals_utils_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguirama <fguirama@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 18:40:00 by fguirama          #+#    #+#             */
/*   Updated: 2023/01/02 18:40:00 by fguirama         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	init_fractal_default(t_fractal *f, int i);
static t_co	default_preset(t_preset preset);

void	init_fractal(t_data *data)
{
	static void	(*init_fractals[N_FRAC])(t_fractal *) = {\
init_mandelbrot, init_julia, init_celtic, init_burning_shipe, init_buffalo, \
init_burning_julia, init_julia3, init_celtic_mandelbar, \
init_perpendicular_celtic, init_heart, init_mandelbar, init_celtic_mandelbrot};
	int			i;

	i = 0;
	while (i < N_FRAC)
	{
		init_fractal_default(data->fractals + i, i % 4);
		init_fractals[i](data->fractals + i);
		data->fractals[i].plan_default = data->fractals[i].plan;
		data->fractals[i].c = data->fractals[i].preset(PRESET_0);
		i++;
	}
	data->f = data->fractals;
}


static void	init_fractal_default(t_fractal *f, int i)
{
	f->size_zoom = 1.6;
	f->plan.start = (t_co){-2, 2};
	f->plan.end = (t_co){2, -2};
	f->preset = default_preset;
	f->max_iter = MAX_ITER;
	f->menu.start = (t_co){((i % 2) == 1) * HWIN, (i >= 2) * HWIN};
	f->menu.end = (t_co){f->menu.start.x + HWIN, f->menu.start.y + HWIN};
	f->start_launch_plan = (t_co){0, 1.3};
}

t_co	default_preset(t_preset preset)
{
	(void)preset;
	return ((t_co){0, 0});
}

void	launch_fractal(t_data *data, t_fractals set)
{
	if (data->in_menu)
	{
		data->f = data->fractals + set;
		set_color(data, data->f->color);
	}
	data->in_menu = FALSE;
	data->c_animate = TRUE;
	data->f->animation_c.start.x = data->f->start_launch_plan.x;
	data->f->animation_c.start.y = data->f->start_launch_plan.y;
	data->f->animation_c.end.x = data->f->c.x;
	data->f->animation_c.end.y = data->f->c.y;
	data->f->plan = data->f->plan_default;
}
