/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frac_burning_ship.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguirama <fguirama@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 12:31:00 by fguirama          #+#    #+#             */
/*   Updated: 2023/01/02 12:31:00 by fguirama         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	init_burning_shipe(t_fractal *f)
{
	f->set = BURNING_SHIP;
	f->plan.start = (t_co){-2.4, 1.6};
	f->plan.end = (t_co){1.6, -2.4};
	f->sequence = burning_shipe;
	f->max_preset = PRESET_0;
	f->color = RED;
	f->name = "Burning Ship";
	f->offset_name = 36;
}

int	burning_shipe(t_data *data, t_fractal *frac, t_co c)
{
	t_co	z;
	t_co	sqr;
	int		i;

	z = (t_co){frac->c.x, frac->c.y};
	sqr = (t_co){pow(z.x, 2), pow(z.y, 2)};
	i = -1;
	while (++i < frac->max_iter)
	{
		z.y = 2 * fabs(z.x * z.y) + c.y;
		z.x = sqr.x - sqr.y + c.x;
		sqr = (t_co){pow(z.x, 2), pow(z.y, 2)};
		if (sqr.x + sqr.y > 4)
			return (get_color(data, frac, i, sqr.x + sqr.y));
	}
	return (FG);
}

t_color	*set_red(t_appearance new_app)
{
	static t_color		pal[5] = {};
	static t_appearance	app = -1;

	if (app != new_app)
	{
		if (new_app == DARK)
		{
			pal[0].color = FG;
			pal[1].color = 0x374140;
			pal[2].color = 0x817A63;
			pal[3].color = 0xD9CB9E;
			pal[4].color = 0xDC3522;
		}
		else
		{
			pal[0].color = 0xF45D4C;
			pal[1].color = 0xF7A541;
			pal[2].color = 0xFACA66;
			pal[3].color = 0xFEE5AD;
			pal[4].color = 0xA1DBB2;
		}
		app = new_app;
	}
	return (pal);
}
