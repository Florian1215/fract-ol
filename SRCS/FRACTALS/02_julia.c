/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frac_julia.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguirama <fguirama@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 12:29:00 by fguirama          #+#    #+#             */
/*   Updated: 2023/01/02 12:29:00 by fguirama         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static t_co	preset_julia(t_preset preset);

void	init_julia(t_fractal *f)
{
	f->set = JULIA;
	f->sequence = julia;
	f->animation_c.start = (t_co){2, -2};
	f->preset = preset_julia;
	f->max_preset = PRESET_6;
	f->color = PURPLE;
}

int	julia(t_data *data, t_fractal *frac, t_co z, t_co co)
{
	int		i;
	t_co	sqr;

	i = 0;
	sqr = (t_co){pow(z.x, 2), pow(z.y, 2)};
	while (i < frac->max_iter)
	{
		z.y = 2 * z.x * z.y - frac->c.y;
		z.x = sqr.x - sqr.y - frac->c.x;
		sqr = (t_co){pow(z.x, 2), pow(z.y, 2)};
		if (sqr.x + sqr.y > 4)
			return (get_color(data, (t_color_data){frac, i, sqr.x + sqr.y}, \
co, z));
		i++;
	}
	return (FG);
}

static t_co	preset_julia(t_preset preset)
{
	static double	presets[PRESET_6 + 1][2] = {
	{0.80, 0},
	{0.75, 0.13},
	{0.82, -0.2},
	{0.76, 0.06},
	{0.18, 0.69},
	{0.76, -0.32},
	{0.8, -0.14},
	};

	return ((t_co){presets[preset][0], presets[preset][1]});
}

#define PURPLE_01	0xB6696A
#define PURPLE_02	0xE8ECF4
#define PURPLE_03	0xE1E2E5
#define PURPLE_04	0xE7CE8C

void	init_purple(t_data *data)
{
	data->pal[PURPLE][LIGHT][0] = (t_color){0x23254C};
	data->pal[PURPLE][LIGHT][1] = (t_color){PURPLE_01};
	data->pal[PURPLE][LIGHT][2] = (t_color){PURPLE_02};
	data->pal[PURPLE][LIGHT][3] = (t_color){PURPLE_03};
	data->pal[PURPLE][LIGHT][4] = (t_color){PURPLE_04};
	data->pal[PURPLE][DARK][0] = (t_color){FG};
	data->pal[PURPLE][DARK][1] = (t_color){PURPLE_01};
	data->pal[PURPLE][DARK][2] = (t_color){PURPLE_02};
	data->pal[PURPLE][DARK][3] = (t_color){PURPLE_03};
	data->pal[PURPLE][DARK][4] = (t_color){PURPLE_04};
}
