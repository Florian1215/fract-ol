/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frac_celtic.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguirama <fguirama@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 12:30:00 by fguirama          #+#    #+#             */
/*   Updated: 2023/01/02 12:30:00 by fguirama         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	init_celtic(t_fractal *f)
{
	f->set = CELTIC;
	f->plan.start = (t_co){-2, 1.3};
	f->plan.end = (t_co){2, -2.7};
	f->sequence = celtic;
	f->color = ELECTRIC_BLUE;
	f->max_preset = PRESET_0;
	f->name = "Celtic";
	f->offset_name = 18;
}

int	celtic(t_data *data, t_fractal *frac, t_co c)
{
	int		i;
	t_co	z;
	t_co	sqr;

	i = -1;
	z = (t_co){c.x, c.y};
	sqr = (t_co){pow(z.x, 2), pow(z.y, 2)};
	while (++i < frac->max_iter)
	{
		z.y = (2 * z.x * z.y) + c.x + frac->c.x;
		z.x = fabs(sqr.x - sqr.y) + c.y + fabs(frac->c.y);
		sqr = (t_co){pow(z.x, 2), pow(z.y, 2)};
		if (sqr.x + sqr.y > 4)
			return (get_color(data, frac, i, sqr.x + sqr.y));
	}
	return (FG);
}

t_color	*set_electric_blue(t_appearance new_app)
{
	static t_color		pal[5] = {{}, {0x007882}, {0x23AA8F}, {0x86D780}, {\
0xFAFA6E}};
	static t_appearance	app = -1;

	if (app != new_app)
	{
		if (new_app == DARK)
			pal[0].color = FG;
		else
			pal[0].color = 0x2A4858;
		app = new_app;
	}
	return (pal);
}
