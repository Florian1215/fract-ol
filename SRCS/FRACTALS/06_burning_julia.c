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

int	burning_julia(t_data *data, t_fractal *frac, t_co c)
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
			return (get_color(data, frac, i, sqr.x + sqr.y));
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

t_color	*set_pink(t_appearance new_app)
{
	static t_color		pal[5] = {};
	static t_appearance	app = -1;

	if (app != new_app)
	{
		if (new_app == DARK)
		{
			pal[0].color = FG;
			pal[1].color = 0x333F58;
			pal[2].color = 0x4A7A96;
			pal[3].color = 0xEE8695;
			pal[4].color = 0xFBBBAD;
		}
		else
		{
			pal[0].color = 0xEE7788;
			pal[1].color = 0xFFCCCC;
			pal[2].color = 0xFF99AA;
			pal[3].color = 0xCC4466;
			pal[4].color = 0x441122;
		}
		app = new_app;
	}
	return (pal);
}
