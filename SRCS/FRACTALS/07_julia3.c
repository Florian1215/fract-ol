/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frac_julia3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguirama <fguirama@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 12:36:00 by fguirama          #+#    #+#             */
/*   Updated: 2023/01/02 12:36:00 by fguirama         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static t_co	preset_julia3(t_preset preset);

void	init_julia3(t_fractal *f)
{
	f->set = JULIA3;
	f->sequence = julia3;
	f->animation_c.start = (t_co){-2, -2};
	f->preset = preset_julia3;
	f->max_preset = PRESET_8;
	f->color = GREEN_BLUE;
	f->offset_name = 35;
}

int	julia3(t_data *data, t_fractal *frac, t_co z, t_co co)
{
	int		i;
	t_co	sqr;

	i = -1;
	sqr = (t_co){pow(z.x, 2), pow(z.y, 2)};
	while (++i < frac->max_iter)
	{
		z.x = sqr.x * z.x - 3 * sqr.y * z.x + frac->c.x;
		z.y = -z.y * z.y * z.y + 3 * sqr.x * z.y + frac->c.y;
		sqr = (t_co){pow(z.x, 2), pow(z.y, 2)};
		if (sqr.x + sqr.y > 4)
			return (get_color(data, frac, i, sqr.x + sqr.y, co));
	}
	return (FG);
}

static t_co	preset_julia3(t_preset preset)
{
	static double	presets[PRESET_8 + 1][2] = {
	{-0.54, 0.45},
	{-0.462, -0.536},
	{-0.452, -0.616},
	{-0.53, -0.166},
	{-0.208, -0.924},
	{-0.538, -0.17},
	{-0.53, -0.456},
	{-0.472, -0.536},
	{-0.53, -0.146},
	};

	return ((t_co){presets[preset][0], presets[preset][1]});
}

t_color	*set_green_blue(t_appearance new_app)
{
	static t_color		pal[5] = {{}, {0xE2F3E4}, {0x94E344}, {\
0x46878F}, {0x332C50}};
	static t_appearance	app = -1;

	if (app != new_app)
	{
		if (new_app == DARK)
			pal[0].color = FG;
		else
			pal[0].color = 0xBEE4C2;
		app = new_app;
	}
	return (pal);
}
