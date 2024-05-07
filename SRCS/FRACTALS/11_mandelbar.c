/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frac_mandelbar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguirama <fguirama@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 12:45:00 by fguirama          #+#    #+#             */
/*   Updated: 2023/01/02 12:45:00 by fguirama         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static t_co	preset_mandelbar(t_preset preset);

void	init_mandelbar(t_fractal *f)
{
	f->set = MANDELBAR;
	f->sequence = mandelbar;
	f->animation_c.start = (t_co){-2, 2};
	f->preset = preset_mandelbar;
	f->max_preset = PRESET_7;
	f->color = BLUE;
}

int	mandelbar(t_data *data, t_fractal *frac, t_co z, t_co co)
{
	int		i;
	t_co	sqr;

	i = 0;
	sqr = (t_co){pow(z.x, 2), pow(z.y, 2)};
	while (i < frac->max_iter)
	{
		z.y = -2 * fabs(z.x) * z.y + frac->c.y;
		z.x = sqr.x - sqr.y + frac->c.x;
		sqr = (t_co){pow(z.x, 2), pow(z.y, 2)};
		if (sqr.x + sqr.y > 4)
			return (get_color(data, (t_color_data){frac, i, sqr.x + sqr.y}, \
co, z));
		i++;
	}
	return (FG);
}

static t_co	preset_mandelbar(t_preset preset)
{
	static double	presets[PRESET_7 + 1][2] = {
	{-0.23, 0.796},
	{-0.272, -0.776},
	{-0.768, -0.296},
	{-0.132, -0.796},
	{-0.352, -0.746},
	{0.416, -0.526},
	{-0.574, -0.506},
	{-0.78, 0.186},
	};

	return ((t_co){presets[preset][0], presets[preset][1]});
}

#define BLUE_02	0x5BACE3
#define BLUE_03	0x636AB8
#define BLUE_04	0x574175

void	init_blue(t_data *data)
{
	data->pal[BLUE][LIGHT][0] = (t_color){0xF7FFED};
	data->pal[BLUE][LIGHT][1] = (t_color){0xB5F5EC};
	data->pal[BLUE][LIGHT][2] = (t_color){BLUE_02};
	data->pal[BLUE][LIGHT][3] = (t_color){BLUE_03};
	data->pal[BLUE][LIGHT][4] = (t_color){BLUE_04};
	data->pal[BLUE][DARK][0] = (t_color){FG};
	data->pal[BLUE][DARK][1] = (t_color){0x82C9FF};
	data->pal[BLUE][DARK][2] = (t_color){BLUE_02};
	data->pal[BLUE][DARK][3] = (t_color){BLUE_03};
	data->pal[BLUE][DARK][4] = (t_color){BLUE_04};
}
