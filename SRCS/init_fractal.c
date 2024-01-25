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
void		init_mandelbrot(t_fractal *f);
void		init_julia(t_fractal *f);
void		init_celtic(t_fractal *f);
void		init_burning_shipe(t_fractal *f);
void		init_buffalo(t_fractal *f);
void		init_burning_julia(t_fractal *f);
void		init_julia3(t_fractal *f);
void		init_celtic_mandelbar(t_fractal *f);
void		init_perpendicular_celtic(t_fractal *f);
void		init_heart(t_fractal *f);
void		init_mandelbar(t_fractal *f);
void		init_celtic_mandelbrot(t_fractal *f);
void		init_hovers(t_data *data);

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
	init_hovers(data);
}


static void	init_fractal_default(t_fractal *f, int i)
{
	f->plan.start = (t_co){-2, 2};
	f->plan.end = (t_co){2, -2};
	f->preset = default_preset;
	f->max_iter = MAX_ITER;
	f->menu.start = (t_co){((i % 2) == 1) * HWIN, (i >= 2) * HWIN};
	f->menu.end = (t_co){f->menu.start.x + HWIN, f->menu.start.y + HWIN};
}

t_co	default_preset(t_preset preset)
{
	(void)preset;
	return ((t_co){0, 0});
}
