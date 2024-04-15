/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frac_burning_julia.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguirama <fguirama@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 12:35:00 by fguirama          #+#    #+#             */
/*   Updated: 2023/01/02 12:35:00 by fguirama         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static t_co	preset_burning_julia(t_preset preset);

void	init_burning_julia(t_fractal *f)
{
	f->set = BURNING_JULIA;
	f->sequence = burning_julia;
	f->animation_c.start = (t_co){2, -2};
	f->preset = preset_burning_julia;
	f->max_preset = PRESET_9;
	f->color = PINK;
	f->offset_name = 45;
}

int	burning_julia(t_data *data, t_fractal *frac, t_co c, t_co co)
{
	t_co	z;
	t_co	sqr;
	int		i;

	z = (t_co){c.x, c.y};
	sqr = (t_co){pow(z.x, 2), pow(z.y, 2)};
	i = -1;
	while (++i < frac->max_iter)
	{
		z.y = fabs(2 * z.x * z.y - frac->c.y);
		z.x = sqr.x - sqr.y - frac->c.x;
		sqr = (t_co){pow(z.x, 2), pow(z.y, 2)};
		if (sqr.x + sqr.y > 4)
			return (get_color(data, frac, i, sqr.x + sqr.y, co));
	}
	return (FG);
}

static t_co	preset_burning_julia(t_preset preset)
{
	static double	presets[PRESET_9 + 1][2] = {
	{0.92, -0.54},
	{1.02, -0.2},
	{0.344, -0.724},
	{-0.216, 0.572},
	{-0.34, -0.03},
	{0.95, 0.12},
	{-0.33, 0.81},
	{-0.232, -0.58},
	{0.88, -0.81},
	{-0.34, -0.06},
	};

	return ((t_co){presets[preset][0], presets[preset][1]});
}

void	init_pink(t_data *data)
{
	data->pal[PINK][LIGHT][0] = (t_color){0xEE7788};
	data->pal[PINK][LIGHT][1] = (t_color){0xFFCCCC};
	data->pal[PINK][LIGHT][2] = (t_color){0xFF99AA};
	data->pal[PINK][LIGHT][3] = (t_color){0xCC4466};
	data->pal[PINK][LIGHT][4] = (t_color){0x441122};

	data->pal[PINK][DARK][0] = (t_color){FG};
	data->pal[PINK][DARK][1] = (t_color){0x333F58};
	data->pal[PINK][DARK][2] = (t_color){0x4A7A96};
	data->pal[PINK][DARK][3] = (t_color){0xEE8695};
	data->pal[PINK][DARK][4] = (t_color){0xFBBBAD};
}
