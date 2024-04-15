/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frac_heart.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguirama <fguirama@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 12:41:00 by fguirama          #+#    #+#             */
/*   Updated: 2023/01/02 12:41:00 by fguirama         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static t_co	preset_heart(t_preset preset);

void	init_heart(t_fractal *f)
{
	f->set = HEART;
	f->sequence = heart;
	f->animation_c.start = (t_co){-1, 2};
	f->preset = preset_heart;
	f->max_preset = PRESET_5;
	f->color = NIGHT_BLUE;
	f->offset_name = 18;
}

int	heart(t_data *data, t_fractal *frac, t_co z, t_co co)
{
	int		i;
	t_co	sqr;

	i = -1;
	sqr = (t_co){pow(z.x, 2), pow(z.y, 2)};
	while (++i < frac->max_iter)
	{
		z.y = 2 * fabs(z.x) * z.y + frac->c.y;
		z.x = sqr.x - sqr.y + frac->c.x;
		sqr = (t_co){pow(z.x, 2), pow(z.y, 2)};
		if (sqr.x + sqr.y > 4)
			return (get_color(data, frac, i, sqr.x + sqr.y, co, z));
	}
	return (FG);
}

static t_co	preset_heart(t_preset preset)
{
	static double	presets[PRESET_5 + 1][2] = {
	{-0.07, 0.278},
	{-0.51, 0.085},
	{-0.982, -0.066},
	{0.29, 0.008},
	{-0.108, -0.26},
	{0.29, -0.012},
	};

	return ((t_co){presets[preset][0], presets[preset][1]});
}

#define NIGHT_BLUE_01	0x494D7E
#define NIGHT_BLUE_02	0xC69FA5
#define NIGHT_BLUE_03	0xF2D3AB
#define NIGHT_BLUE_04	0xFBF5EF

void	init_night_blue(t_data *data)
{
	data->pal[NIGHT_BLUE][LIGHT][0] = (t_color){0x272744};
	data->pal[NIGHT_BLUE][LIGHT][1] = (t_color){NIGHT_BLUE_01};
	data->pal[NIGHT_BLUE][LIGHT][2] = (t_color){NIGHT_BLUE_02};
	data->pal[NIGHT_BLUE][LIGHT][3] = (t_color){NIGHT_BLUE_03};
	data->pal[NIGHT_BLUE][LIGHT][4] = (t_color){NIGHT_BLUE_04};

	data->pal[NIGHT_BLUE][DARK][0] = (t_color){FG};
	data->pal[NIGHT_BLUE][DARK][1] = (t_color){NIGHT_BLUE_01};
	data->pal[NIGHT_BLUE][DARK][2] = (t_color){NIGHT_BLUE_02};
	data->pal[NIGHT_BLUE][DARK][3] = (t_color){NIGHT_BLUE_03};
	data->pal[NIGHT_BLUE][DARK][4] = (t_color){NIGHT_BLUE_04};
}
