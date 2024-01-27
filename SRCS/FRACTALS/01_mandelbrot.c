/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frac_mandelbrot.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguirama <fguirama@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 12:28:00 by fguirama          #+#    #+#             */
/*   Updated: 2023/01/02 12:28:00 by fguirama         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	init_mandelbrot(t_fractal *f)
{
	f->set = MANDELBROT;
	f->plan.start.x = -2.2;
	f->plan.end.x = 1.8;
	f->sequence = mandelbrot;
	f->max_preset = PRESET_0;
	f->color = GREEN;
	f->offset_name = 20;
}

int	mandelbrot(t_data *data, t_fractal *frac, t_co c)
{
	t_co	z;
	int		i;
	t_co	sqr;

	z = (t_co){frac->c.x, frac->c.y};
	sqr = (t_co){pow(z.x, 2), pow(z.y, 2)};
	i = -1;
	while (++i < frac->max_iter)
	{
		z.y = 2 * z.x * z.y + c.y;
		z.x = sqr.x - sqr.y + c.x;
		sqr = (t_co){pow(z.x, 2), pow(z.y, 2)};
		if (sqr.x + sqr.y > 4)
			return (get_color(data, frac, i, sqr.x + sqr.y));
	}
	return (FG);
}

t_color	*set_green(t_appearance new_app)
{
	static t_color		pal[5] = {{}, {}, {0xFFB03B}, {0xB64926}, {0x8E2800}};
	static t_appearance	app = -1;

	if (app != new_app)
	{
		if (new_app == DARK)
		{
			pal[0].color = FG;
			pal[1].color = 0x295E52;
		}
		else
		{
			pal[0].color = 0x468966;
			pal[1].color = 0xFFF0A5;
		}
		app = new_app;
	}
	return (pal);
}
