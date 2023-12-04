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
	f->name = "Heart";
	f->offset_name = 18;
}

int	heart(t_data *data, t_fractal *frac, t_co z)
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
			return (get_color(data, frac, i, sqr.x + sqr.y));
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

t_color	*set_night_blue(t_appearance new_app)
{
	static t_color		pal[5] = {{}, {0x494D7E}, {0xC69FA5}, {\
0xF2D3AB}, {0xFBF5EF}};
	static t_appearance	app = -1;

	if (app != new_app)
	{
		if (new_app == DARK)
			pal[0].color = FG;
		else
			pal[0].color = 0x272744;
		app = new_app;
	}
	return (pal);
}
