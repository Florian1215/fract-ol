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
	f->offset_menu = (t_co){-125, -125};
	f->animation_c.start = (t_co){2, -2};
	f->preset = preset_julia;
	f->max_preset = PRESET_6;
	f->color = PURPLE;
	f->name = "Julia";
	f->offset_name = 19;
}

int	julia(t_data *data, t_fractal *frac, t_co z)
{
	int		i;
	t_co	sqr;

	i = -1;
	sqr = (t_co){pow(z.x, 2), pow(z.y, 2)};
	while (++i < frac->max_iter)
	{
		z.y = 2 * z.x * z.y - frac->c.y;
		z.x = sqr.x - sqr.y - frac->c.x;
		sqr = (t_co){pow(z.x, 2), pow(z.y, 2)};
		if (sqr.x + sqr.y > 4)
			return (get_color(data, frac, i, sqr.x + sqr.y));
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

t_color	*set_purple(t_appearance new_app)
{
	static t_color		pal[5] = {{}, {0xB6696A}, {0xE8ECF4}, {\
0xE1E2E5}, {0xE7CE8C}};
	static t_appearance	app = -1;

	if (app != new_app)
	{
		if (new_app == DARK)
			pal[0].color = FG;
		else
			pal[0].color = 0x23254C;
		app = new_app;
	}
	return (pal);
}
