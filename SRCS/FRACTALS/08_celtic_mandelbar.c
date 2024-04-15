/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frac_celtic_mandelbar.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguirama <fguirama@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 12:37:00 by fguirama          #+#    #+#             */
/*   Updated: 2023/01/02 12:37:00 by fguirama         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static t_co	preset_celtic_mandelbar(t_preset preset);

void	init_celtic_mandelbar(t_fractal *f)
{
	f->set = CELTIC_MANDELBAR;
	f->sequence = celtic_mandelbar;
	f->animation_c.start = (t_co){-2, -2};
	f->preset = preset_celtic_mandelbar;
	f->max_preset = PRESET_4;
	f->color = BLUE_LIGHT;
	f->offset_name = 50;
}

int	celtic_mandelbar(t_data *data, t_fractal *frac, t_co z, t_co co)
{
	int		i;
	t_co	sqr;

	i = -1;
	sqr = (t_co){pow(z.x, 2), pow(z.y, 2)};
	while (++i < frac->max_iter)
	{
		z.y = -2 * z.x * z.y + frac->c.y;
		z.x = fabs(sqr.x - sqr.y) + frac->c.x;
		sqr = (t_co){pow(z.x, 2), pow(z.y, 2)};
		if (sqr.x + sqr.y > 4)
			return (get_color(data, frac, i, sqr.x + sqr.y, co, z));
	}
	return (FG);
}

static t_co	preset_celtic_mandelbar(t_preset preset)
{
	static double	presets[PRESET_4 + 1][2] = {
	{-0.78, -0.18},
	{-1.66, 0.0},
	{0.276, -0.024},
	{0.096, -0.852},
	{-0.796000, -0.048000}
	};

	return ((t_co){presets[preset][0], presets[preset][1]});
}

#define BLUE_LIGHT_01	0x8ECDE6
#define BLUE_LIGHT_02	0x66A1FF
#define BLUE_LIGHT_03	0x6B61FF
#define BLUE_LIGHT_04	0xFADDA2

void	init_blue_light(t_data *data)
{
	data->pal[BLUE_LIGHT][LIGHT][0] = (t_color){0xF0EFF4};
	data->pal[BLUE_LIGHT][LIGHT][1] = (t_color){BLUE_LIGHT_01};
	data->pal[BLUE_LIGHT][LIGHT][2] = (t_color){BLUE_LIGHT_02};
	data->pal[BLUE_LIGHT][LIGHT][3] = (t_color){BLUE_LIGHT_03};
	data->pal[BLUE_LIGHT][LIGHT][4] = (t_color){BLUE_LIGHT_04};

	data->pal[BLUE_LIGHT][DARK][0] = (t_color){FG};
	data->pal[BLUE_LIGHT][DARK][1] = (t_color){BLUE_LIGHT_01};
	data->pal[BLUE_LIGHT][DARK][2] = (t_color){BLUE_LIGHT_02};
	data->pal[BLUE_LIGHT][DARK][3] = (t_color){BLUE_LIGHT_03};
	data->pal[BLUE_LIGHT][DARK][4] = (t_color){BLUE_LIGHT_04};
}
