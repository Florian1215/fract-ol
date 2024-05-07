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
}

int	celtic_mandelbrot(t_data *data, t_fractal *frac, t_co z, t_co co)
{
	int		i;
	t_co	sqr;

	i = 0;
	sqr = (t_co){pow(z.x, 2), pow(z.y, 2)};
	while (i < frac->max_iter)
	{
		z.y = 2 * z.x * z.y + frac->c.y;
		z.x = fabs(sqr.x - sqr.y) + frac->c.x;
		sqr = (t_co){pow(z.x, 2), pow(z.y, 2)};
		if (sqr.x + sqr.y > 4)
			return (get_color(data, (t_color_data){frac, i, sqr.x + sqr.y}, \
co, z));
		i++;
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

#define YELLOW_01	0xE8AD80
#define YELLOW_02	0xCF784C
#define YELLOW_03	0xAD5845
#define YELLOW_04	0x73383E

void	init_yellow(t_data *data)
{
	data->pal[YELLOW][LIGHT][0] = (t_color){0xF5E5BF};
	data->pal[YELLOW][LIGHT][1] = (t_color){YELLOW_01};
	data->pal[YELLOW][LIGHT][2] = (t_color){YELLOW_02};
	data->pal[YELLOW][LIGHT][3] = (t_color){YELLOW_03};
	data->pal[YELLOW][LIGHT][4] = (t_color){YELLOW_04};
	data->pal[YELLOW][DARK][0] = (t_color){FG};
	data->pal[YELLOW][DARK][1] = (t_color){YELLOW_01};
	data->pal[YELLOW][DARK][2] = (t_color){YELLOW_02};
	data->pal[YELLOW][DARK][3] = (t_color){YELLOW_03};
	data->pal[YELLOW][DARK][4] = (t_color){YELLOW_04};
}
