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
	f->offset_name = 30;
}

int	mandelbar(t_data *data, t_fractal *frac, t_co z)
{
	int		i;
	t_co	sqr;

	i = -1;
	sqr = (t_co){pow(z.x, 2), pow(z.y, 2)};
	while (++i < frac->max_iter)
	{
		z.y = -2 * fabs(z.x) * z.y + frac->c.y;
		z.x = sqr.x - sqr.y + frac->c.x;
		sqr = (t_co){pow(z.x, 2), pow(z.y, 2)};
		if (sqr.x + sqr.y > 4)
			return (get_color(data, frac, i, sqr.x + sqr.y));
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

t_color	*set_blue(t_appearance new_app)
{
	static t_color		pal[5] = {{}, {}, {0x5BACE3}, {\
0x636AB8}, {0x574175}};
	static t_appearance	app = -1;

	if (app != new_app)
	{
		if (new_app == DARK)
		{
			pal[0].color = FG;
			pal[1].color = 0x82C9FF;
		}
		else
		{
			pal[0].color = 0xF7FFED;
			pal[1].color = 0xB5F5EC;
		}
		app = new_app;
	}
	return (pal);
}
