/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frac_buffalo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguirama <fguirama@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 12:33:00 by fguirama          #+#    #+#             */
/*   Updated: 2023/01/02 12:33:00 by fguirama         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static t_co	preset_buffalo(t_preset preset);

void	init_buffalo(t_fractal *f)
{
	f->set = BUFFALO;
	f->plan.start = (t_co){-2.1, 2.1};
	f->plan.end = (t_co){2.1, -2.1};
	f->sequence = buffalo;
	f->animation_c.start = (t_co){-1, 1};
	f->preset = preset_buffalo;
	f->max_preset = PRESET_9;
	f->color = BLUE_RED;
	f->offset_name = 25;
}

int	buffalo(t_data *data, t_fractal *frac, t_co z, t_co co)
{
	int		i;
	t_co	sqr;

	i = -1;
	sqr = (t_co){pow(z.x, 2), pow(z.y, 2)};
	while (++i < frac->max_iter)
	{
		z.y = 2 * fabs(z.x * z.y) + frac->c.y;
		z.x = fabs(sqr.x - sqr.y) + frac->c.x;
		sqr = (t_co){pow(z.x, 2), pow(z.y, 2)};
		if (sqr.x + sqr.y > 4)
			return (get_color(data, frac, i, sqr.x + sqr.y, co));
	}
	return (FG);
}

static t_co	preset_buffalo(t_preset preset)
{
	static double	presets[PRESET_9 + 1][2] = {
	{-1.14, 0.06},
	{0.406, -0.936},
	{-0.936, 0.052},
	{0.536, -1.026},
	{-1.752, -0.544},
	{0.366, -0.676},
	{-1.552, -1.772},
	{-1.13, 0.08},
	{-0.428, -1.52},
	{0.426, -0.716},
	};

	return ((t_co){presets[preset][0], presets[preset][1]});
}

t_color	*set_blue_red(t_appearance new_app)
{
	static t_color		pal[5] = {};
	static t_appearance	app = -1;

	if (app != new_app)
	{
		if (new_app == DARK)
		{
			pal[0].color = FG;
			pal[1].color = 0x263248;
			pal[2].color = 0x7E8AA2;
			pal[3].color = 0xE3DFBB;
			pal[4].color = 0xF0642A;
		}
		else
		{
			pal[0].color = 0x00748E;
			pal[1].color = 0xE3DFBB;
			pal[2].color = 0xF4BA4D;
			pal[3].color = 0xE3753C;
			pal[4].color = 0xDA3B3A;
		}
		app = new_app;
	}
	return (pal);
}
