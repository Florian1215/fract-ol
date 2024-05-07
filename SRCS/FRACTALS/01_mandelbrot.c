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
}

int	mandelbrot(t_data *data, t_fractal *frac, t_co c, t_co co)
{
	t_co	z;
	int		i;
	t_co	sqr;

	z = (t_co){frac->c.x, frac->c.y};
	sqr = (t_co){pow(z.x, 2), pow(z.y, 2)};
	i = 0;
	while (i < frac->max_iter)
	{
		z.y = 2 * z.x * z.y + c.y;
		z.x = sqr.x - sqr.y + c.x;
		sqr = (t_co){pow(z.x, 2), pow(z.y, 2)};
		if (sqr.x + sqr.y > 4)
			return (get_color(data, (t_color_data){frac, i, sqr.x + sqr.y}, \
co, z));
		i++;
	}
	return (FG);
}

#define GREEN_02	0xFFB03B
#define GREEN_03	0xB64926
#define GREEN_04	0x8E2800

void	init_green(t_data *data)
{
	data->pal[GREEN][LIGHT][0] = (t_color){0x468966};
	data->pal[GREEN][LIGHT][1] = (t_color){0xFFF0A5};
	data->pal[GREEN][LIGHT][2] = (t_color){GREEN_02};
	data->pal[GREEN][LIGHT][3] = (t_color){GREEN_03};
	data->pal[GREEN][LIGHT][4] = (t_color){GREEN_04};
	data->pal[GREEN][DARK][0] = (t_color){FG};
	data->pal[GREEN][DARK][1] = (t_color){0x295E52};
	data->pal[GREEN][DARK][2] = (t_color){GREEN_02};
	data->pal[GREEN][DARK][3] = (t_color){GREEN_03};
	data->pal[GREEN][DARK][4] = (t_color){GREEN_04};
}
