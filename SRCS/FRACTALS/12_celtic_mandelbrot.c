/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frac_celtic_mandelbrot.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguirama <fguirama@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 12:38:00 by fguirama          #+#    #+#             */
/*   Updated: 2023/01/02 12:38:00 by fguirama         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static t_co	preset_celtic_mandelbrot(t_preset preset);

void	init_celtic_mandelbrot(t_fractal *f)
{
	f->set = CELTIC_MANDELBROT;
	f->sequence = celtic_mandelbrot;
	f->animation_c.start = (t_co){-2, 2};
	f->preset = preset_celtic_mandelbrot;
	f->max_preset = PRESET_5;
	f->color = YELLOW;
	f->name = "Celtic Mandelbrot";
	f->offset_name = 60;
}

int	celtic_mandelbrot(t_data *data, t_fractal *frac, t_co z)
{
	int		i;
	t_co	sqr;

	i = -1;
	sqr = (t_co){pow(z.x, 2), pow(z.y, 2)};
	while (++i < frac->max_iter)
	{
		z.y = 2 * z.x * z.y + frac->c.y;
		z.x = fabs(sqr.x - sqr.y) + frac->c.x;
		sqr = (t_co){pow(z.x, 2), pow(z.y, 2)};
		if (sqr.x + sqr.y > 4)
			return (get_color(data, frac, i, sqr.x + sqr.y));
	}
	return (FG);
}

static t_co	preset_celtic_mandelbrot(t_preset preset)
{
	static double	presets[PRESET_5 + 1][2] = {
	{-0.816000, 0.128000},
	{-0.804000, -0.320000},
	{-1.184000, -0.252000},
	{-0.872000, -0.804000},
	{-0.562000, -1.044000},
	{-1.260000, -0.008000},
	};

	return ((t_co){presets[preset][0], presets[preset][1]});
}

t_color	*set_yellow(t_appearance new_app)
{
	static t_color		pal[5] = {{}, {0xE8AD80}, {0xCF784C}, {\
0xAD5845}, {0x73383E}};
	static t_appearance	app = -1;

	if (app != new_app)
	{
		if (new_app == DARK)
			pal[0].color = FG;
		else
			pal[0].color = 0xF5E5BF;
		app = new_app;
	}
	return (pal);
}
