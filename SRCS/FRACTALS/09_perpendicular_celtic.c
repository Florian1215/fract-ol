/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frac_perpendicular_celtic.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguirama <fguirama@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 12:41:00 by fguirama          #+#    #+#             */
/*   Updated: 2023/01/02 12:41:00 by fguirama         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static t_co	preset_perpendicular_celtic(t_preset preset);

void	init_perpendicular_celtic(t_fractal *f)
{
	f->set = PERPENDICULAR_CELTIC;
	f->sequence = perpendicular_celtic;
	f->animation_c.start = (t_co){2, 2};
	f->preset = preset_perpendicular_celtic;
	f->max_preset = PRESET_7;
	f->color = PASTEL_PINK;
}

int	perpendicular_celtic(t_data *data, t_fractal *frac, t_co z, t_co co)
{
	int		i;
	t_co	sqr;

	i = 0;
	sqr = (t_co){pow(z.x, 2), pow(z.y, 2)};
	while (i < frac->max_iter)
	{
		z.y = -2 * fabs(z.x) * z.y + frac->c.y;
		z.x = fabs(sqr.x - sqr.y) + frac->c.x;
		sqr = (t_co){pow(z.x, 2), pow(z.y, 2)};
		if (sqr.x + sqr.y > 4)
			return (get_color(data, (t_color_data){frac, i, sqr.x + sqr.y}, \
co, z));
		i++;
	}
	return (FG);
}

static t_co	preset_perpendicular_celtic(t_preset preset)
{
	static double	presets[PRESET_7 + 1][2] = {
	{-0.75, -0.09},
	{-0.796, 0.23},
	{-0.648, -1.08},
	{-0.664, 1.02},
	{0.068, -0.828},
	{-0.824, -0.128},
	{0.292, -0.20},
	{-0.204, -1.04},
	};

	return ((t_co){presets[preset][0], presets[preset][1]});
}

#define PASTEL_PINK_01	0xFFB3CB
#define PASTEL_PINK_02	0xF7FFAE
#define PASTEL_PINK_03	0x96FBC7
#define PASTEL_PINK_04	0x74569B

void	init_pastel_pink(t_data *data)
{
	data->pal[PASTEL_PINK][LIGHT][0] = (t_color){0xD8BFD8};
	data->pal[PASTEL_PINK][LIGHT][1] = (t_color){PASTEL_PINK_01};
	data->pal[PASTEL_PINK][LIGHT][2] = (t_color){PASTEL_PINK_02};
	data->pal[PASTEL_PINK][LIGHT][3] = (t_color){PASTEL_PINK_03};
	data->pal[PASTEL_PINK][LIGHT][4] = (t_color){PASTEL_PINK_04};
	data->pal[PASTEL_PINK][DARK][0] = (t_color){FG};
	data->pal[PASTEL_PINK][DARK][1] = (t_color){PASTEL_PINK_01};
	data->pal[PASTEL_PINK][DARK][2] = (t_color){PASTEL_PINK_02};
	data->pal[PASTEL_PINK][DARK][3] = (t_color){PASTEL_PINK_03};
	data->pal[PASTEL_PINK][DARK][4] = (t_color){PASTEL_PINK_04};
}
